```flow
st=>start: 开始
op=>operation: My Operation
cond=>condition: Yes or No?
e=>end
st->op->cond
cond(yes)->e
cond(no)->op


web=>start: WEB set
chg=>operation: cell_3g_4g_exchange_proc
pre_init=>operation: at_cmd_pre_init
at_send=>operation: at_cmd_send
read=>operation: read_reply_from_modem
parse=>operation: parse_reply_from_modem
return_parse=>operation: return::parse_reply_from_modem
send_ok=>condition: send succ?
read_read_ok=>condition: read succ?
lct=>condition: at+lct?
readfi=>condition: recv \r\n ?
func_parse=>operation: .func_parse()
parse_ret=>condition: switch(parse_ret)
sw_acl=>condition: switch(acp.acl)
send2=>operation: send_init_at_cmd()
err_retry_time=>condition: remain retry times?
end=>end

web->chg->pre_init->at_send->send_ok
send_ok(no)->chg
send_ok(yes)->read->read_read_ok
read_read_ok(no)->end
read_read_ok(yes)->parse->lct
lct(r1 == NULL)->readfi
readfi(yes)->func_parse
func_parse->parse_ret
parse_ret(0)->sw_acl //failed
sw_acl(AT_CMD_ERR_PASS)->send2
sw_acl(AT_CMD_ERR_STOP)->return_parse
sw_acl(AT_CMD_ERR_RETRY_PASS)->send2
sw_acl(AT_CMD_ERR_RETRY_STOP)->err_retry_time
err_retry_time(some)->send2
err_retry_time(none)->return_parse

parse_ret(1)->send2  //success
parse_ret(2)->return_parse  //reset model
readfi(no)->return_parse

lct(COMMAND NOT SUPPORT)->func_parse
lct(ERROR)->func_parse
lct(OK)->func_parse
lct(other)->
&```
