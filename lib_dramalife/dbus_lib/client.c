#include "dbus_inc.h"
#include "demo.h"

#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(int agrc, char** argv) {
  int ret = 0;
  char* name = "test.method.client";
  char* value = "hello furong";
  DBusConnection* conn_session;
  DBusConnection* conn_system;

  printf("%s start\n", name);

  if (0 > (ret = dbus_init(&conn_session, DBUS_BUS_SESSION, name))) {
    return ret;
  }
  //#define TEST_SYSTEM_METHOD	1

#ifdef TEST_SYSTEM_METHOD
  if (0 > (ret = dbus_init(&conn_system, DBUS_BUS_SYSTEM, "xxxx.xxxx"))) {
    return ret;
  }
#endif

  while (1) {
    usrdbus_send_signal_string(conn_session, "/test/signal/Object",
                               DEMO_DBUS_SIGNAL_INTERFACE,
                               DEMO_DBUS_SIGNAL_MEMBER, value);
    sleep(1);

#ifdef TEST_SYSTEM_METHOD
    char* ptr = NULL;
    int reply_int = 0;
    usrdbus_send_method_call_parse_reply(
        conn_system, DEMO_DBUS_METHOD_DEST, DEMO_DBUS_METHOD_PATH,
        DEMO_DBUS_SIGNAL_INTERFACE, "mget", "want_bool", DBUS_TYPE_BOOLEAN,
        &reply_int);

    usrdbus_send_method_call_parse_reply(conn_system, DEMO_DBUS_METHOD_DEST,
                                         DEMO_DBUS_METHOD_PATH,
                                         DEMO_DBUS_SIGNAL_INTERFACE, "mget",
                                         "want_string", DBUS_TYPE_STRING, &ptr);
#endif

    sleep(1);
  }

  return 0;
}
#endif
