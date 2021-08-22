#include "dbus_inc.h"

int usrdbus_send_method_call_parse_reply(DBusConnection* pconn,
                                         const char* arg_destination,
                                         const char* arg_path,
                                         const char* arg_iface,
                                         const char* arg_method,
                                         const char* arg_param,
                                         int arg_reply_type,
                                         void* arg_reply_mem) {
  dbus_uint32_t serial = 0;
  DBusMessage *msg, *msg_ret;
  DBusMessageIter args;
  DBusError err;

  dbus_error_init(&err);

  msg = dbus_message_new_method_call(arg_destination, arg_path, arg_iface,
                                     arg_method);

  if (NULL == msg) {
    fprintf(stderr, "dbus_message_new_signal error\n");
    return -1;
  }

  dbus_message_iter_init_append(msg, &args);
  if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &arg_param)) {
    fprintf(stderr, "dbus_message_iter_append_basic error\n");
    return -1;
  }

  if (NULL != (msg_ret = dbus_connection_send_with_reply_and_block(
                   pconn, msg, 2000, &err))) {
    if (!dbus_message_iter_init(msg_ret, &args)) {
      printf("no arg!\n");
    } else {
      int type = 0;
      if ((type = dbus_message_iter_get_arg_type(&args)) != arg_reply_type) {
        printf("type err! 0x%x\n", type);
      }
      dbus_message_iter_get_basic(&args, arg_reply_mem);
      switch (arg_reply_type) {
        case DBUS_TYPE_STRING:
          if (*(char**)arg_reply_mem) {
            printf("ret:%s\n", *(char**)arg_reply_mem);
          }
          break;
        case DBUS_TYPE_BOOLEAN:
          printf("reply=%d\n", *(int*)arg_reply_mem);
          break;
        default:
          printf("unknown type 0x%x\n", arg_reply_type);
          break;
      }
    }
  } else {
    if (dbus_error_is_set(&err)) {
      printf("===%s\n", err.message);
      dbus_error_free(&err);
    }
  }

  if (msg)
    dbus_message_unref(msg);
  if (msg_ret)
    dbus_message_unref(msg_ret);

  return 0;
}
