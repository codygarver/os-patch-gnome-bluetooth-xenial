/*
 * Generated by gdbus-codegen 2.47.4. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __BLUETOOTH_FDO_GLUE_H__
#define __BLUETOOTH_FDO_GLUE_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for org.freedesktop.DBus.ObjectManager */

#define TYPE_OBJECT_MANAGER (object_manager_get_type ())
#define OBJECT_MANAGER(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_MANAGER, ObjectManager))
#define IS_OBJECT_MANAGER(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_MANAGER))
#define OBJECT_MANAGER_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_OBJECT_MANAGER, ObjectManagerIface))

struct _ObjectManager;
typedef struct _ObjectManager ObjectManager;
typedef struct _ObjectManagerIface ObjectManagerIface;

struct _ObjectManagerIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_get_managed_objects) (
    ObjectManager *object,
    GDBusMethodInvocation *invocation);

  void (*interfaces_added) (
    ObjectManager *object,
    const gchar *arg_object,
    GVariant *arg_interfaces);

  void (*interfaces_removed) (
    ObjectManager *object,
    const gchar *arg_object,
    const gchar *const *arg_interfaces);

};

GType object_manager_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *object_manager_interface_info (void);
guint object_manager_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void object_manager_complete_get_managed_objects (
    ObjectManager *object,
    GDBusMethodInvocation *invocation,
    GVariant *objects);



/* D-Bus signal emissions functions: */
void object_manager_emit_interfaces_added (
    ObjectManager *object,
    const gchar *arg_object,
    GVariant *arg_interfaces);

void object_manager_emit_interfaces_removed (
    ObjectManager *object,
    const gchar *arg_object,
    const gchar *const *arg_interfaces);



/* D-Bus method calls: */
void object_manager_call_get_managed_objects (
    ObjectManager *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean object_manager_call_get_managed_objects_finish (
    ObjectManager *proxy,
    GVariant **out_objects,
    GAsyncResult *res,
    GError **error);

gboolean object_manager_call_get_managed_objects_sync (
    ObjectManager *proxy,
    GVariant **out_objects,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_OBJECT_MANAGER_PROXY (object_manager_proxy_get_type ())
#define OBJECT_MANAGER_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_MANAGER_PROXY, ObjectManagerProxy))
#define OBJECT_MANAGER_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_OBJECT_MANAGER_PROXY, ObjectManagerProxyClass))
#define OBJECT_MANAGER_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_OBJECT_MANAGER_PROXY, ObjectManagerProxyClass))
#define IS_OBJECT_MANAGER_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_MANAGER_PROXY))
#define IS_OBJECT_MANAGER_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_OBJECT_MANAGER_PROXY))

typedef struct _ObjectManagerProxy ObjectManagerProxy;
typedef struct _ObjectManagerProxyClass ObjectManagerProxyClass;
typedef struct _ObjectManagerProxyPrivate ObjectManagerProxyPrivate;

struct _ObjectManagerProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  ObjectManagerProxyPrivate *priv;
};

struct _ObjectManagerProxyClass
{
  GDBusProxyClass parent_class;
};

GType object_manager_proxy_get_type (void) G_GNUC_CONST;

void object_manager_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ObjectManager *object_manager_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
ObjectManager *object_manager_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void object_manager_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
ObjectManager *object_manager_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
ObjectManager *object_manager_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_OBJECT_MANAGER_SKELETON (object_manager_skeleton_get_type ())
#define OBJECT_MANAGER_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_OBJECT_MANAGER_SKELETON, ObjectManagerSkeleton))
#define OBJECT_MANAGER_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_OBJECT_MANAGER_SKELETON, ObjectManagerSkeletonClass))
#define OBJECT_MANAGER_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_OBJECT_MANAGER_SKELETON, ObjectManagerSkeletonClass))
#define IS_OBJECT_MANAGER_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_OBJECT_MANAGER_SKELETON))
#define IS_OBJECT_MANAGER_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_OBJECT_MANAGER_SKELETON))

typedef struct _ObjectManagerSkeleton ObjectManagerSkeleton;
typedef struct _ObjectManagerSkeletonClass ObjectManagerSkeletonClass;
typedef struct _ObjectManagerSkeletonPrivate ObjectManagerSkeletonPrivate;

struct _ObjectManagerSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  ObjectManagerSkeletonPrivate *priv;
};

struct _ObjectManagerSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType object_manager_skeleton_get_type (void) G_GNUC_CONST;

ObjectManager *object_manager_skeleton_new (void);


/* ------------------------------------------------------------------------ */
/* Declarations for org.freedesktop.DBus.Properties */

#define TYPE_PROPERTIES (properties_get_type ())
#define PROPERTIES(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_PROPERTIES, Properties))
#define IS_PROPERTIES(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_PROPERTIES))
#define PROPERTIES_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_PROPERTIES, PropertiesIface))

struct _Properties;
typedef struct _Properties Properties;
typedef struct _PropertiesIface PropertiesIface;

struct _PropertiesIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_get) (
    Properties *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_interface,
    const gchar *arg_name);

  gboolean (*handle_get_all) (
    Properties *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_interface);

  gboolean (*handle_set) (
    Properties *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_interface,
    const gchar *arg_name,
    GVariant *arg_value);

  void (*properties_changed) (
    Properties *object,
    const gchar *arg_interface,
    GVariant *arg_changed_properties,
    const gchar *const *arg_invalidated_properties);

};

GType properties_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *properties_interface_info (void);
guint properties_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void properties_complete_get (
    Properties *object,
    GDBusMethodInvocation *invocation,
    GVariant *value);

void properties_complete_set (
    Properties *object,
    GDBusMethodInvocation *invocation);

void properties_complete_get_all (
    Properties *object,
    GDBusMethodInvocation *invocation,
    GVariant *properties);



/* D-Bus signal emissions functions: */
void properties_emit_properties_changed (
    Properties *object,
    const gchar *arg_interface,
    GVariant *arg_changed_properties,
    const gchar *const *arg_invalidated_properties);



/* D-Bus method calls: */
void properties_call_get (
    Properties *proxy,
    const gchar *arg_interface,
    const gchar *arg_name,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean properties_call_get_finish (
    Properties *proxy,
    GVariant **out_value,
    GAsyncResult *res,
    GError **error);

gboolean properties_call_get_sync (
    Properties *proxy,
    const gchar *arg_interface,
    const gchar *arg_name,
    GVariant **out_value,
    GCancellable *cancellable,
    GError **error);

void properties_call_set (
    Properties *proxy,
    const gchar *arg_interface,
    const gchar *arg_name,
    GVariant *arg_value,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean properties_call_set_finish (
    Properties *proxy,
    GAsyncResult *res,
    GError **error);

gboolean properties_call_set_sync (
    Properties *proxy,
    const gchar *arg_interface,
    const gchar *arg_name,
    GVariant *arg_value,
    GCancellable *cancellable,
    GError **error);

void properties_call_get_all (
    Properties *proxy,
    const gchar *arg_interface,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean properties_call_get_all_finish (
    Properties *proxy,
    GVariant **out_properties,
    GAsyncResult *res,
    GError **error);

gboolean properties_call_get_all_sync (
    Properties *proxy,
    const gchar *arg_interface,
    GVariant **out_properties,
    GCancellable *cancellable,
    GError **error);



/* ---- */

#define TYPE_PROPERTIES_PROXY (properties_proxy_get_type ())
#define PROPERTIES_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_PROPERTIES_PROXY, PropertiesProxy))
#define PROPERTIES_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_PROPERTIES_PROXY, PropertiesProxyClass))
#define PROPERTIES_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_PROPERTIES_PROXY, PropertiesProxyClass))
#define IS_PROPERTIES_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_PROPERTIES_PROXY))
#define IS_PROPERTIES_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_PROPERTIES_PROXY))

typedef struct _PropertiesProxy PropertiesProxy;
typedef struct _PropertiesProxyClass PropertiesProxyClass;
typedef struct _PropertiesProxyPrivate PropertiesProxyPrivate;

struct _PropertiesProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  PropertiesProxyPrivate *priv;
};

struct _PropertiesProxyClass
{
  GDBusProxyClass parent_class;
};

GType properties_proxy_get_type (void) G_GNUC_CONST;

void properties_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
Properties *properties_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
Properties *properties_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void properties_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
Properties *properties_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
Properties *properties_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_PROPERTIES_SKELETON (properties_skeleton_get_type ())
#define PROPERTIES_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_PROPERTIES_SKELETON, PropertiesSkeleton))
#define PROPERTIES_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_PROPERTIES_SKELETON, PropertiesSkeletonClass))
#define PROPERTIES_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_PROPERTIES_SKELETON, PropertiesSkeletonClass))
#define IS_PROPERTIES_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_PROPERTIES_SKELETON))
#define IS_PROPERTIES_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_PROPERTIES_SKELETON))

typedef struct _PropertiesSkeleton PropertiesSkeleton;
typedef struct _PropertiesSkeletonClass PropertiesSkeletonClass;
typedef struct _PropertiesSkeletonPrivate PropertiesSkeletonPrivate;

struct _PropertiesSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  PropertiesSkeletonPrivate *priv;
};

struct _PropertiesSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType properties_skeleton_get_type (void) G_GNUC_CONST;

Properties *properties_skeleton_new (void);


G_END_DECLS

#endif /* __BLUETOOTH_FDO_GLUE_H__ */
