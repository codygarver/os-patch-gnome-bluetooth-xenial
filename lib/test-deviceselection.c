/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2005-2008  Marcel Holtmann <marcel@holtmann.org>
 *  Copyright (C) 2006-2007  Bastien Nocera <hadess@hadess.net>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>

#include "bluetooth-chooser.h"
#include "bluetooth-chooser-button.h"
#include "bluetooth-chooser-combo.h"
#include "bluetooth-chooser-private.h"
#include "bluetooth-client.h"
#include "bluetooth-client-private.h"
#include "bluetooth-utils.h"
#include "bluetooth-filter-widget.h"

static void select_device_changed(BluetoothChooser *sel,
				  gchar *address, gpointer user_data)
{
	GtkDialog *dialog = user_data;
	char *name;

	name = bluetooth_chooser_get_selected_device_name (sel);
	gtk_dialog_set_response_sensitive(dialog,
				GTK_RESPONSE_ACCEPT, (address != NULL && name != NULL));
	g_free (name);
}

static void selected_device_activated(BluetoothChooser *sel,
				      gchar *address, gpointer user_data)
{
	GtkDialog *dialog = user_data;

	gtk_dialog_response(dialog, GTK_RESPONSE_ACCEPT);
}

static void device_selected_cb(GObject *object,
			       GParamSpec *spec, gpointer user_data)
{
	g_message ("Property \"device-selected\" changed");
	if (bluetooth_chooser_get_selected_device (BLUETOOTH_CHOOSER (object)))
		bluetooth_chooser_dump_selected_device (BLUETOOTH_CHOOSER (object));
}

static void device_type_filter_selected_cb(GObject *object,
					   GParamSpec *spec, gpointer user_data)
{
	g_message ("Property \"device-type-filter\" changed");
}

static void device_category_filter_selected_cb(GObject *object,
				GParamSpec *spec, gpointer user_data)
{
	g_message ("Property \"device-category-filter\" changed");
}

/* Phone chooser */

static void
chooser_created (BluetoothChooserButton *button, BluetoothChooser *chooser, gpointer data)
{
	g_object_set(chooser,
		     "show-searching", FALSE,
		     "show-pairing", FALSE,
		     "show-device-type", FALSE,
		     "device-type-filter", BLUETOOTH_TYPE_PHONE,
		     "show-device-category", FALSE,
		     "device-category-filter", BLUETOOTH_CATEGORY_PAIRED,
		     NULL);
}

static void
is_available_changed (GObject    *gobject,
		      GParamSpec *pspec,
		      gpointer    user_data)
{
	gboolean is_available;

	g_object_get (gobject, "is-available", &is_available, NULL);
	g_message ("button is available: %d", is_available);
	gtk_widget_set_sensitive (GTK_WIDGET (gobject), is_available);
}

static void
device_changed (GObject    *gobject,
		GParamSpec *pspec,
		gpointer    user_data)
{
	char *device;

	g_object_get (gobject, "device", &device, NULL);
	g_message ("Property \"device\" changed to '%s'", device);

	g_free (device);
}

static GtkWidget *
create_phone_dialogue (const char *bdaddr)
{
	GtkWidget *dialog, *button;

	dialog = g_object_new(GTK_TYPE_DIALOG,
			      "use-header-bar", 1,
			      "title", "My test prefs",
			      NULL);
	button = bluetooth_chooser_button_new ();
	if (bdaddr != NULL)
		g_object_set (G_OBJECT (button), "device", bdaddr, NULL);
	g_signal_connect (G_OBJECT (button), "chooser-created",
			  G_CALLBACK (chooser_created), NULL);
	g_signal_connect (G_OBJECT (button), "notify::is-available",
			  G_CALLBACK (is_available_changed), NULL);
	g_signal_connect (G_OBJECT (button), "notify::device",
			  G_CALLBACK (device_changed), NULL);
	is_available_changed (G_OBJECT (button), NULL, NULL);
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (dialog))),
			    button, TRUE, TRUE, 0);

	g_signal_connect (G_OBJECT (dialog), "response",
			  G_CALLBACK (gtk_main_quit), NULL);

	g_object_add_weak_pointer (G_OBJECT(dialog), (gpointer *) (&dialog));

	return dialog;
}

/* Wizard and co. */
static GtkWidget *
create_dialogue (const char *title)
{
	GtkWidget *dialog, *button;
	GtkStyleContext *context;

	dialog = g_object_new (GTK_TYPE_DIALOG,
			       "use-header-bar", 1,
			       "title", title,
			       NULL);
	gtk_dialog_add_buttons(GTK_DIALOG (dialog),
			       "_Cancel", GTK_RESPONSE_CANCEL,
			       "Connect", GTK_RESPONSE_ACCEPT, NULL);
	gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog),
					GTK_RESPONSE_ACCEPT, FALSE);
	gtk_window_set_default_size(GTK_WINDOW(dialog), 480, 400);

	gtk_container_set_border_width (GTK_CONTAINER (dialog), 5);
	gtk_box_set_spacing (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (dialog))), 2);

	button = gtk_dialog_get_widget_for_response(GTK_DIALOG (dialog), GTK_RESPONSE_ACCEPT);
	context = gtk_widget_get_style_context(button);
	gtk_style_context_add_class (context, "suggested-action");

	return dialog;
}

static void
response_cb (GtkDialog *dialog, gint response_id, BluetoothChooser *selector)
{
	if (response_id == GTK_RESPONSE_ACCEPT) {
		char *address, *name, *icon;
		guint type;

		address = bluetooth_chooser_get_selected_device (selector);
		name = bluetooth_chooser_get_selected_device_name (selector);
		icon = bluetooth_chooser_get_selected_device_icon (selector);
		type = bluetooth_chooser_get_selected_device_type (selector);
		g_message("Selected device is: %s (address: %s, icon: %s, type: %s)",
			  name, address, icon, bluetooth_type_to_string (type));
		g_free(address);
		g_free (name);
		g_free (icon);
	} else {
		g_message ("No selected device");
	}

	if (response_id == GTK_RESPONSE_DELETE_EVENT)
		exit (0);

	gtk_main_quit ();
}

static GtkWidget *
create_wizard_dialogue (void)
{
	GtkWidget *dialog, *selector;

	dialog = create_dialogue ("Add a Device");

	selector = bluetooth_chooser_new();
	gtk_container_set_border_width(GTK_CONTAINER(selector), 5);
	gtk_widget_show(selector);
	g_object_set(selector,
		     "show-searching", TRUE,
		     "show-device-type", TRUE,
		     "show-device-category", FALSE,
		     "device-category-filter", BLUETOOTH_CATEGORY_NOT_PAIRED_OR_TRUSTED,
		     NULL);

	g_signal_connect(selector, "selected-device-changed",
			 G_CALLBACK(select_device_changed), dialog);
	g_signal_connect(selector, "notify::device-selected",
			 G_CALLBACK(device_selected_cb), dialog);
	g_signal_connect(selector, "notify::device-type-filter",
			 G_CALLBACK(device_type_filter_selected_cb), dialog);
	g_signal_connect(selector, "notify::device-category-filter",
			 G_CALLBACK(device_category_filter_selected_cb), dialog);
	g_signal_connect(selector, "selected-device-activated",
			 G_CALLBACK(selected_device_activated), dialog);
	gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG(dialog))), selector,
			    TRUE, TRUE, 0);
	bluetooth_chooser_start_discovery (BLUETOOTH_CHOOSER (selector));

	g_signal_connect (G_OBJECT (dialog), "response",
			  G_CALLBACK (response_cb), selector);

	return dialog;
}

static GtkWidget *
create_props_dialogue (void)
{
	GtkWidget *dialog, *selector;

	dialog = create_dialogue ("Add a Device");

	selector = bluetooth_chooser_new();
	gtk_container_set_border_width(GTK_CONTAINER(selector), 5);
	gtk_widget_show(selector);
	g_object_set(selector,
		     "show-searching", FALSE,
		     "show-device-type", FALSE,
		     "show-device-category", FALSE,
		     "show-pairing", TRUE,
		     "show-connected", TRUE,
		     "device-category-filter", BLUETOOTH_CATEGORY_PAIRED_OR_TRUSTED,
		     NULL);

	g_signal_connect(selector, "selected-device-changed",
			 G_CALLBACK(select_device_changed), dialog);
	g_signal_connect(selector, "notify::device-selected",
			 G_CALLBACK(device_selected_cb), dialog);
	g_signal_connect(selector, "notify::device-type-filter",
			 G_CALLBACK(device_type_filter_selected_cb), dialog);
	g_signal_connect(selector, "notify::device-category-filter",
			 G_CALLBACK(device_category_filter_selected_cb), dialog);
	g_signal_connect(selector, "selected-device-activated",
			 G_CALLBACK(selected_device_activated), dialog);
	gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG(dialog))), selector,
			    TRUE, TRUE, 0);

	g_signal_connect (G_OBJECT (dialog), "response",
			  G_CALLBACK (response_cb), selector);

	return dialog;
}

static void device_changed_cb (GObject *object,
			       GParamSpec *spec,
			       GtkDialog *dialog)
{
	char *device;
	BluetoothChooser *chooser;
	GtkWidget *tree;
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	GtkTreeIter iter;

	g_object_get (object, "device", &device, NULL);
	g_message ("Property \"device\" changed to '%s'", device);

	gtk_dialog_set_response_sensitive (dialog,
					  GTK_RESPONSE_ACCEPT,
					  device != NULL);

	g_object_get (object, "chooser", &chooser, NULL);
	tree = bluetooth_chooser_get_treeview (BLUETOOTH_CHOOSER (chooser));
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree));
	gtk_tree_selection_get_selected (selection, &model, &iter);
	if (model != NULL)
		bluetooth_client_dump_device (model, &iter);

	g_object_unref (chooser);
	g_free (device);
}

static GtkWidget *
create_combo_dialogue (const char *bdaddr)
{
	GtkWidget *dialog, *selector, *chooser;
	const char *filter = "OBEXObjectPush";
//	const char *filter[] = { "OBEXObjectPush", "OBEXFileTransfer", NULL };

	dialog = create_dialogue ("Add a Device");

	selector = bluetooth_chooser_combo_new ();
	g_signal_connect (G_OBJECT (selector), "notify::device",
			  G_CALLBACK (device_changed_cb), dialog);
	g_object_get (G_OBJECT (selector), "chooser", &chooser, NULL);
	g_object_set(chooser,
		     "show-searching", TRUE,
		     "show-device-type", TRUE,
		     "show-device-category", TRUE,
		     "show-pairing", TRUE,
		     "show-connected", FALSE,
		     "device-service-filter", filter,
		     NULL);
	g_object_set (G_OBJECT (selector), "device", bdaddr, NULL);
	bluetooth_chooser_start_discovery (BLUETOOTH_CHOOSER (chooser));
	gtk_container_set_border_width(GTK_CONTAINER(selector), 5);
	gtk_widget_show(selector);
	gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (dialog))),
			    selector, TRUE, FALSE, 6);

	g_signal_connect (G_OBJECT (dialog), "response",
			  G_CALLBACK (response_cb), chooser);

	return dialog;
}

static GtkWidget *
create_filter_dialogue (void)
{
	GtkWidget *dialog, *selector, *filter, *vbox, *hbox;

	dialog = create_dialogue ("Add a Device");

	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_widget_show (hbox);

	selector = bluetooth_chooser_new();
	gtk_container_set_border_width(GTK_CONTAINER(selector), 5);
	gtk_widget_show(selector);
	g_object_set(selector,
		     "show-searching", TRUE,
		     "device-category-filter", BLUETOOTH_CATEGORY_NOT_PAIRED_OR_TRUSTED,
		     NULL);
	gtk_box_pack_start (GTK_BOX (hbox), selector, TRUE, TRUE, 6);

	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_show (vbox);
	gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
	filter = bluetooth_filter_widget_new ();
	g_object_set (filter,
		      "show-device-type", TRUE,
		      "show-device-category", FALSE,
		      NULL);
	gtk_widget_show (filter);
	bluetooth_filter_widget_bind_filter (BLUETOOTH_FILTER_WIDGET (filter), BLUETOOTH_CHOOSER (selector));
	gtk_box_pack_start (GTK_BOX (vbox), filter, FALSE, FALSE, 6);

	g_signal_connect(selector, "selected-device-changed",
			 G_CALLBACK(select_device_changed), dialog);
	g_signal_connect(selector, "notify::device-selected",
			 G_CALLBACK(device_selected_cb), dialog);
	g_signal_connect(selector, "notify::device-type-filter",
			 G_CALLBACK(device_type_filter_selected_cb), dialog);
	g_signal_connect(selector, "notify::device-category-filter",
			 G_CALLBACK(device_category_filter_selected_cb), dialog);
	gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (dialog))),
			    hbox, TRUE, TRUE, 0);
	bluetooth_chooser_start_discovery (BLUETOOTH_CHOOSER (selector));

	g_signal_connect (G_OBJECT (dialog), "response",
			  G_CALLBACK (response_cb), selector);

	return dialog;
}

int main(int argc, char **argv)
{
	GtkWidget *dialog;
	const char *selection;

	gtk_init(&argc, &argv);
	if (argc < 2)
		selection = "wizard";
	else
		selection = argv[1];

	if (g_str_equal (selection, "phone")) {
		if (argc == 3)
			dialog = create_phone_dialogue (argv[2]);
		else
			dialog = create_phone_dialogue (NULL);
	} else if (g_str_equal (selection, "wizard")) {
		dialog = create_wizard_dialogue ();
	} else if (g_str_equal (selection, "props")) {
		dialog = create_props_dialogue ();
	} else if (g_str_equal (selection, "combo")) {
		if (argc == 3)
			dialog = create_combo_dialogue (argv[2]);
		else
			dialog = create_combo_dialogue (BLUETOOTH_CHOOSER_COMBO_FIRST_DEVICE);
	} else if (g_str_equal (selection, "filter")) {
		dialog = create_filter_dialogue ();
	} else {
		g_warning ("Unknown dialogue type, try either \"phone\", \"props\", \"combo\", \"filter\"  or \"wizard\"");
		return 1;
	}

	gtk_widget_show(dialog);

	gtk_main ();

	if (dialog)
		gtk_widget_destroy(dialog);

	return 0;
}
