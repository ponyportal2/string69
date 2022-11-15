#include <stdbool.h>
#include <stddef.h>

// переделаем нуллы и size_t вот в это под конец:
// #define s21_size_t unsigned long long
// #define s21_NULL (void *)0

size_t s21_strlen(const char *str);
char *s21_strstr(char *str1, char *str2);
void *s21_memchr(const void *arr, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
// s21_memcpy: если n больше размера заданного массива, то оригинал выдает
// ошибку, если одна строка вывод не тот
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memmove(void *dest, const void *src, size_t n);
// s21_memset: оригинал ошибка если n больше размера массива
void *s21_memset(void *str, int c, size_t n);

// s21_strcat: вставляет ли в конец строки \0
// char *s21_strcat(char *str1, const char *str2); // karnhor
// char *s21_strncat(char *str1, const char *str2, size_t n); // karnhor

char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, size_t n);

// char *s21_strcpy(char *dest, const char *src); // karnhor

char *s21_strcpy_helper(char *dest, const char *src, size_t n,
                        bool isNcopy); // sharkmer
char *s21_strcpy(char *dest, const char *src); // sharkmer
char *s21_strncpy(char *dest, const char *src, size_t n); // sharkmer

char *s21_strcat_helper(char *dest, const char *src, size_t n, bool isNcat); // sharkmer
char *s21_strcat(char *dest, const char *src); // sharkmer
char *s21_strncat(char *dest, const char *src, size_t n); // sharkmer

char *s21_strrchr(const char *str, int c);
size_t s21_strspn(const char *stringOne, const char *stringTwo);
size_t s21_strcspn(const char *stringOne, const char *stringTwo);

char *s21_strtok (char *str, const char *delim);
char *s21_strpbrk(const char *str, const char *sym);
char *s21_strerror(int errcode);

// helper functions:
bool s21_match(const char *inputCharArr, char inputChar);
size_t s21_strspn_helper(const char *stringOne, const char *stringTwo,
                         bool isCspn);

                         
static char *ErrorNames[] = {
  "Undefined error: 0",
"Operation not permitted",
"No such file or directory",
"No such process",
"Interrupted system call",
"Input/output error",
"Device not configured",
"Argument list too long",
"Exec format error",
"Bad file descriptor",
"No child processes",
"Resource deadlock avoided",
"Cannot allocate memory",
"Permission denied",
"Bad address",
"Block device required",
"Resource busy",
"File exists",
"Cross-device link",
"Operation not supported by device",
"Not a directory",
"Is a directory",
"Invalid argument",
"Too many open files in system",
"Too many open files",
"Inappropriate ioctl for device",
"Text file busy",
"File too large",
"No space left on device",
"Illegal seek",
"Read-only file system",
"Too many links",
"Broken pipe",
"Numerical argument out of domain",
"Result too large",
"Resource temporarily unavailable",
"Operation now in progress",
"Operation already in progress",
"Socket operation on non-socket",
"Destination address required",
"Message too long",
"Protocol wrong type for socket",
"Protocol not available",
"Protocol not supported",
"Socket type not supported",
"Operation not supported",
"Protocol family not supported",
"Address family not supported by protocol family",
"Address already in use",
"Can't assign requested address",
"Network is down",
"Network is unreachable",
"Network dropped connection on reset",
"Software caused connection abort",
"Connection reset by peer",
"No buffer space available",
"Socket is already connected",
"Socket is not connected",
"Can't send after socket shutdown",
"Too many references: can't splice",
"Operation timed out",
"Connection refused",
"Too many levels of symbolic links",
"File name too long",
"Host is down",
"No route to host",
"Directory not empty",
"Too many processes",
"Too many users",
"Disc quota exceeded",
"Stale NFS file handle",
"Too many levels of remote in path",
"RPC struct is bad",
"RPC version wrong",
"RPC prog. not avail",
"Program version wrong",
"Bad procedure for program",
"No locks available",
"Function not implemented",
"Inappropriate file type or format",
"Authentication error",
"Need authenticator",
"Device power is off",
"Device error",
"Value too large to be stored in data type",
"Bad executable (or shared library)",
"Bad CPU type in executable",
"Shared library version mismatch",
"Malformed Mach-o file",
"Operation canceled",
"Identifier removed",
"No message of desired type",
"Illegal byte sequence",
"Attribute not found",
"Bad message",
"EMULTIHOP (Reserved)",
"No message available on STREAM",
"ENOLINK (Reserved)",
"No STREAM resources",
"Not a STREAM",
"Protocol error",
"STREAM ioctl timeout",
"Operation not supported on socket",
"Policy not found",
"State not recoverable",
"Previous owner died",
"Interface output queue is full"
};

enum Errors {
  Undefined_error_0,
Operation_not_permitted,
No_such_file_or_directory,
No_such_process,
Interrupted_system_call,
Input_output_error,
Device_not_configured,
Argument_list_too_long,
Exec_format_error,
Bad_file_descriptor,
No_child_processes,
Resource_deadlock_avoided,
Cannot_allocate_memory,
Permission_denied,
Bad_address,
Block_device_required,
Resource_busy,
File_exists,
Cross_device_link,
Operation_not_supported_by_device,
Not_a_directory,
Is_a_directory,
Invalid_argument,
Too_many_open_files_in_system,
Too_many_open_files,
Inappropriate_ioctl_for_device,
Text_file_busy,
File_too_large,
No_space_left_on_device,
Illegal_seek,
Read_only_file_system,
Too_many_links,
Broken_pipe,
Numerical_argument_out_of_domain,
Result_too_large,
Resource_temporarily_unavailable,
Operation_now_in_progress,
Operation_already_in_progress,
Socket_operation_on_non_socket,
Destination_address_required,
Message_too_long,
Protocol_wrong_type_for_socket,
Protocol_not_available,
Protocol_not_supported,
Socket_type_not_supported,
Operation_not_supported,
Protocol_family_not_supported,
Address_family_not_supported_by_protocol_family,
Address_already_in_use,
Cant_assign_requested_address,
Network_is_down,
Network_is_unreachable,
Network_dropped_connection_on_reset,
Software_caused_connection_abort,
Connection_reset_by_peer,
No_buffer_space_available,
Socket_is_already_connected,
Socket_is_not_connected,
Cant_send_after_socket_shutdown,
Too_many_references_cant_splice,
Operation_timed_out,
Connection_refused,
Too_many_levels_of_symbolic_links,
File_name_too_long,
Host_is_down,
No_route_to_host,
Directory_not_empty,
Too_many_processes,
Too_many_users,
Disc_quota_exceeded,
Stale_NFS_file_handle,
Too_many_levels_of_remote_in_path,
RPC_struct_is_bad,
RPC_version_wrong,
RPC_prog_not_avail,
Program_version_wrong,
Bad_procedure_for_program,
No_locks_available,
Function_not_implemented,
Inappropriate_file_type_or_format,
Authentication_error,
Need_authenticator,
Device_power_is_off,
Device_error,
Value_too_large_to_be_stored_in_data_type,
Bad_executable_or_shared_library,
Bad_CPU_type_in_executable,
Shared_library_version_mismatch,
Malformed_Mach_o_file,
Operation_canceled,
Identifier_removed,
No_message_of_desired_type,
Illegal_byte_sequence,
Attribute_not_found,
Bad_message,
EMULTIHOP_Reserved,
No_message_available_on_STREAM,
ENOLINK_Reserved,
No_STREAM_resources,
Not_a_STREAM,
Protocol_error,
STREAM_ioctl_timeout,
Operation_not_supported_on_socket,
Policy_not_found,
State_not_recoverable,
Previous_owner_died,
Interface_output_queue_is_full
};