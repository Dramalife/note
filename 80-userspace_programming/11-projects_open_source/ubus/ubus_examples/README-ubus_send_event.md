#### Test function "ubus_send_event"
```bash
####
# Compile
# Server compile > "server_dl_event.out"
make server_with_dl_object_event


####
# Test
# Terminal 1
sudo ./server_dl_event.out
# Terminal 2
sudo ubus listen
# Terminal 3
sudo ubus list -v
sudo ubus call dlobj dlset '{"dlarg1":1,"dlarg2":"1"}'
```
