#include "dbus_inc.h"

int usrdbus_send_signal_string(DBusConnection* pconn,
                               const char* arg_path,
                               const char* arg_iface,
                               const char* arg_name,
                               const char* arg_value) {
  dbus_uint32_t serial = 0;
  DBusMessage* msg;
  DBusMessageIter args;

  msg = dbus_message_new_signal(arg_path,   // object name
                                arg_iface,  // interface name
                                arg_name);  // name of signal

  if (NULL == msg) {
    fprintf(stderr, "dbus_message_new_signal error\n");
    return -1;
  }

  dbus_message_iter_init_append(msg, &args);
  if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &arg_value)) {
    fprintf(stderr, "dbus_message_iter_append_basic error\n");
    return -1;
  }

  if (!dbus_connection_send(pconn, msg, &serial)) {
    fprintf(stderr, "dbus_connection_send error\n");
    return -1;
  }

  printf("usrdbus_send_signal_string: %s\n", arg_value);

  dbus_connection_flush(pconn);

  dbus_message_unref(msg);

  return 0;
}

int dldbus_read_signal_block(DBusConnection* pconn,
                             const char* a_match,
                             const char* a_interface,
                             const char* a_member) {
  DBusMessage* message;
  DBusMessageIter args;
  DBusError error;
  dbus_error_init(&error);

  if (a_match) {
    dbus_bus_add_match(pconn, a_match, &error);

    if (dbus_error_is_set(&error)) {
      fprintf(stderr, "dbus_bus_add_match: %s\n", error.message);
      return -1;
    }
  }

  while (1) {
    /* As long as the connection is open, this function will block until it can
     * read or write, then read or write, then return TRUE. */
    if (FALSE == dbus_connection_read_write(pconn, 0)) {
      printf("Connection closed!");
      return -__LINE__;
    }

    /* Returns the first-received message from the incoming message queue,
     * removing it from the queue. */
    if (NULL == (message = dbus_connection_pop_message(pconn))) {
      sleep(1);
      continue;
    }

    /* Checks whether the message is a signal with the given interface and
     * member fields.  */
    if (dbus_message_is_signal(message, a_interface, a_member)) {
      printf(">\n");
      if (!dbus_message_iter_init(message, &args)) {
        fprintf(stderr, "dbus_message_is_signal error\n");
      } else {
        int current_type = -1;
        while (DBUS_TYPE_INVALID !=
               (current_type = dbus_message_iter_get_arg_type(&args))) {
          void* value;

          /* The returned value is by reference and should not be freed. */
          dbus_message_iter_get_basic(&args, &value);
          switch (current_type) {
            case DBUS_TYPE_UINT32: {
              printf("dbus_message_iter_get_basic: %d\n", (dbus_uint32_t)value);
            } break;
            case DBUS_TYPE_BOOLEAN: {
              printf("dbus_message_iter_get_basic: %d\n", (dbus_bool_t)value);
            } break;
            case DBUS_TYPE_STRING: {
              printf("dbus_message_iter_get_basic: %s\n", (const char*)value);
            } break;
            case DBUS_TYPE_BYTE:
              break;
            default:
              break;
          }
          dbus_message_iter_next(&args);
        }
      }
    }

    dbus_message_unref(message);
  }
}
