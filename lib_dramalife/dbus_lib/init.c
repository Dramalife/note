#include "dbus_inc.h"

int dbus_init(DBusConnection** ppconn, DBusBusType type, char const* name) {
  DBusError error;
  int ret = 0;

  dbus_error_init(&error);

  /* 建立与D-Bus后台的连接 */
  *ppconn = dbus_bus_get(type, &error);
  if (dbus_error_is_set(&error)) {
    fprintf(stderr, "dbus_bus_get: %s\n", error.message);
    dbus_error_free(&error);
    return -1;
  }

  ///* 给连接分配一个名字 不是必须*/
  // ret = dbus_bus_request_name(*ppconn, name, DBUS_NAME_FLAG_REPLACE_EXISTING,
  // &error); if(dbus_error_is_set(&error)) { 	fprintf(stderr,
  //"dbus_bus_request_name: %s\n", error.message); 	dbus_error_free(&error);
  //	return -1;
  //}
  // if(DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
  //	return -1;
  //}

  return 0;
}
