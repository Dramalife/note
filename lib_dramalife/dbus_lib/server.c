#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "demo.h"

#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(int agrc, char** argv) {
  int ret = 0;
  char* name = DEMO_DBUS_NAME;

  DBusConnection* conn_session;
  DBusConnection* conn_system;

  printf("%s start\n", name);

  if (0 > (ret = dbus_init(&conn_session, DBUS_BUS_SESSION, name))) {
    return ret;
  }

  while (1) {
    dldbus_read_signal_block(
        conn_session,
        "type='signal', interface='" DEMO_DBUS_SIGNAL_INTERFACE "'",
        DEMO_DBUS_SIGNAL_INTERFACE, DEMO_DBUS_SIGNAL_MEMBER);
  }

  return 0;
}
#endif
