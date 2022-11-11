
#include <kernel.h>

//const int8_t *msg110 = (uint8_t*)"110 Restart marker reply.\r\n";
/*
         110 Restart marker reply.
             In this case, the text is exact and not left to the
             particular implementation; it must read:
                  MARK yyyy = (int8_t*)mmmm
             Where yyyy is User-process data stream marker, and mmmm
             server's equivalent marker (note the spaces between markers
             and "=").
*/
//const int8_t *msg120 = (int8_t*)"120 Service ready in nnn minutes.\r\n";
//const int8_t *msg125 = (int8_t*)"125 Data connection already open; transfer starting.\r\n";
const int8_t *msg150 = (int8_t*)"150 File status okay; about to open data connection.\r\n";
const int8_t *msg150recv = (int8_t*)"150 Opening BINARY mode data connection\r\n";
const int8_t *msg150stor = (int8_t*)"150 Opening BINARY mode data connection.\r\n";
const int8_t *msg200 = (int8_t*)"200 Command okay.\r\n";
//const int8_t *msg202 = (int8_t*)"202 Command not implemented, superfluous at this site.\r\n";
//const int8_t *msg211 = (int8_t*)"211 System status, or system help reply.\r\n";
//const int8_t *msg212 = (int8_t*)"212 Directory status.\r\n";
//const int8_t *msg213 = (int8_t*)"213 File status.\r\n";
//const int8_t *msg214 = (int8_t*)"214 Help message.\r\n";
/*
             214 Help message.
             On how to use the server or the meaning of a particular
             non-standard command.  This reply is useful only to the
             human user.
*/
const int8_t *msg214SYST = (int8_t*)"214 system type.\r\n";
/*
         215 NAME system type.
             Where NAME is an official system name from the list in the
             Assigned Numbers document.
*/
const int8_t *msg220 = (int8_t*)"220 tinet FTP Server ready.\r\n";
/*
         220 Service ready for new user.
*/
const int8_t *msg221 = (int8_t*)"221 Goodbye.\r\n";
/*
         221 Service closing control connection.
             Logged out if appropriate.
*/
//const int8_t *msg225 = (int8_t*)"225 Data connection open;\r\n";
const int8_t *msg226 = (int8_t*)"226 Closing data connection.\r\n";
/*
             Requested file action successful (for example, file
             transfer or file abort).
*/
const int8_t *msg227_short = (int8_t*)"227 Entering Passive Mode \r\n";
//const int8_t *msg227 = (int8_t*)"227 Entering Passive Mode (%i,%i,%i,%i,%i,%i).\r\n";   /////////////////////
/*
         227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).
*/
const int8_t *msg230 = (int8_t*)"230 User logged in, proceed.\r\n";
const int8_t *msg250 = (int8_t*)"250 Requested file action okay, completed.\r\n";
const int8_t *msg257PWD = (int8_t*)"257 current directory is \"%s \r\n";
const int8_t *msg257 = (int8_t*)"257 created \"%s\r\n";
/*
         257 "PATHNAME" created.
*/
const int8_t *msg331 = (int8_t*)"331 User name okay, need password.\r\n";
//const int8_t *msg332 = (int8_t*)"332 Need account for login.\r\n";
const int8_t *msg350 = (int8_t*)"350 Requested file action pending further information.\r\n";
//const int8_t *msg421 = (int8_t*)"421 Service not available, closing control connection.\r\n";
/*
             This may be a reply to any command if the service knows it
             must shut down.
*/
//const int8_t *msg425 = (int8_t*)"425 Can't open data connection.\r\n";
//const int8_t *msg426 = (int8_t*)"426 Connection closed; transfer aborted.\r\n";
const int8_t *msg450 = (int8_t*)"450 Requested file action not taken.\r\n";
/*
             File unavailable (e.g., file busy).
*/
const int8_t *msg451 = (int8_t*)"451 Requested action aborted.\r\n";
//const int8_t *msg452 = (int8_t*)"452 Requested action not taken.\r\n";
/*
             Insufficient storage space in system.
*/
//const int8_t *msg500 = (int8_t*)"500 Syntax error, command unrecognized.\r\n";
/*
             This may include errors such as command line too long.
*/
const int8_t *msg501 = (int8_t*)"501 Syntax error in parameters or arguments.\r\n";
const int8_t *msg502 = (int8_t*)"502 Command not implemented.\r\n";
const int8_t *msg503 = (int8_t*)"503 Bad sequence of commands.\r\n";
//const int8_t *msg504 = (int8_t*)"504 Command not implemented for that parameter.\r\n";
//const int8_t *msg530 = (int8_t*)"530 Not logged in.\r\n";
const int8_t *msg532 = (int8_t*)"532 Need account for storing files.\r\n";
const int8_t *msg550 = (int8_t*)"550 Requested action not taken.\r\n";
/*
             File unavailable (e.g., file not found, no access).
*/
const int8_t *msg551 = (int8_t*)"551 Requested action aborted: page type unknown.\r\n";
const int8_t *msg552 = (int8_t*)"552 Requested file action aborted.\r\n";
/*
             Exceeded storage allocation (for current directory or
             dataset).
*/
const int8_t *msg553 = (int8_t*)"553 Requested action not taken.\r\n";
/*
             File name not allowed.
*/
