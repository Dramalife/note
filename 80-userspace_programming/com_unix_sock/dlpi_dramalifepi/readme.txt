
typedef struct dlpi_frame
{
char *des_sock_path;	//specific sock path
u8_t mechine_specific_code[2];	//specific mechine, not useful yet.
u8_t lll_type[2];	//(toDES|to_others|)
u8_t global_data_struct_code[2];	//16 bit.
void *buffer;	//(trans_to_datastruct|trans_to_DES_level)
}dlpi_frame;

