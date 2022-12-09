

#ifndef FTPD_MESSEAGE_H
#define FTPD_MESSEAGE_H

extern const int8_t *msg110;
/*
         110 Restart marker reply.
             In this case, the text is exact and not left to the
             particular implementation; it must read:
                  MARK yyyy = mmmm
             Where yyyy is User-process data stream marker, and mmmm
             server's equivalent marker (note the spaces between markers
             and "=").
*/
extern const int8_t *msg120;
extern const int8_t *msg125;
extern const int8_t *msg150;
extern const int8_t *msg150recv;
extern const int8_t *msg150stor;
extern const int8_t *msg200;
extern const int8_t *msg202;
extern const int8_t *msg211;
extern const int8_t *msg212;
extern const int8_t *msg213;
extern const int8_t *msg214;
/*
             214 Help message.
             On how to use the server or the meaning of a particular
             non-standard command.  This reply is useful only to the
             human user.
*/
extern const int8_t *msg214SYST;
/*
         215 NAME system type.
             Where NAME is an official system name from the list in the
             Assigned Numbers document.
*/
extern const int8_t *msg220;
/*
         220 Service ready for new user.
*/
extern const int8_t *msg221;
/*
         221 Service closing control connection.
             Logged out if appropriate.
*/
extern const int8_t *msg225;
extern const int8_t *msg226;
/*
             Requested file action successful (for example, file
             transfer or file abort).
*/
extern const int8_t *msg227_short;
extern const int8_t *msg227;
/*
         227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).
*/
extern const int8_t *msg230;
extern const int8_t *msg250;
extern const int8_t *msg257PWD;
extern const int8_t *msg257;
/*
         257 "PATHNAME" created.
*/
extern const int8_t *msg331;
extern const int8_t *msg332;
extern const int8_t *msg350;
extern const int8_t *msg421;
/*
             This may be a reply to any command if the service knows it
             must shut down.
*/
extern const int8_t *msg425;
extern const int8_t *msg426;
extern const int8_t *msg450;
/*
             File unavailable (e.g., file busy).
*/
extern const int8_t *msg451;
extern const int8_t *msg452;
/*
             Insufficient storage space in system.
*/
extern const int8_t *msg500;
/*
             This may include errors such as command line too long.
*/
extern const int8_t *msg501;
extern const int8_t *msg502;
extern const int8_t *msg503;
extern const int8_t *msg504;
extern const int8_t *msg530;
extern const int8_t *msg532;
extern const int8_t *msg550;
/*
             File unavailable (e.g., file not found, no access).
*/
extern const int8_t *msg551;
extern const int8_t *msg552;
/*
             Exceeded storage allocation (for current directory or
             dataset).
*/
extern const int8_t *msg553;
/*
             File name not allowed.
*/


void send_msg(ID cep_id, struct ftpd_msgstate *fsm, const int8_t *msg);




#endif
