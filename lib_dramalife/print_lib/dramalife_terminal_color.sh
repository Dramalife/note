# Terminal print color library
#
# https://github.com/Dramalife/note.git
# Dramalife@live.com
#
# 2019.11.14
# 2020.01.12
# 2020.03.20
#	Update : Change version to 5002, Make variable names more canonical.
#



################################
#	Version	Code		#
################################
#LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5001
LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5002



# This is the "5002" version.
# DLCLR - Dramalife Print Lib Of Terminal
DLTERM_NONE=		"\e[0m"
DLTERM_RED=		"\e[0;31m"
DLTERM_LRED=		"\e[1;31m"
DLTERM_GREEN=		"\e[0;32m"
DLTERM_LGREEN=		"\e[1;32m"
DLTERM_BLACK=		"\e[0;30m"
DLTERM_LBLACK=		"\e[1;30m"
DLTERM_BROWN=		"\e[0;33m"
DLTERM_YELLOW=		"\e[1;33m"
DLTERM_BLUE=		"\e[0;34m"
DLTERM_LBLUE=		"\e[1;34m"
DLTERM_PURPLE=		"\e[0;35m"
DLTERM_LPURPLE=		"\e[1;35m"
DLTERM_CYAN=		"\e[0;36m"
DLTERM_LCYAN=		"\e[1;36m"
DLTERM_GRAY=		"\e[0;37m"
DLTERM_WHITE=		"\e[1;37m"
DLTERM_BOLD=		"\e[1m"
DLTERM_UNDERLINE=	"\e[4m"
DLTERM_BLINK=		"\e[5m"
DLTERM_REVERSE=		"\e[7m"
DLTERM_HIDE=		"\e[8m"
DLTERM_CLEAR=		"\e[2J"
DLTERM_CLRLINE=		"\r\e[K"


# This is the "5001" version.
# For compatibility with version "5001"
CNONE=		$(DLTERM_NONE)
CRED=	        $(DLTERM_RED)
CLRED=	        $(DLTERM_LRED)
CGREEN=	        $(DLTERM_GREEN)
CLGREEN=	$(DLTERM_LGREEN)
BLACK=	        $(DLTERM_BLACK)
L_BLACK=	$(DLTERM_LBLACK)
BROWN=	        $(DLTERM_BROWN)
YELLOW=	        $(DLTERM_YELLOW)
BLUE=	        $(DLTERM_BLUE)
L_BLUE=	        $(DLTERM_LBLUE)
PURPLE=	        $(DLTERM_PURPLE)
L_PURPLE=	$(DLTERM_LPURPLE)
CYAN=	        $(DLTERM_CYAN)
L_CYAN=	        $(DLTERM_LCYAN)
GRAY=	        $(DLTERM_GRAY)
WHITE=	        $(DLTERM_WHITE)
BOLD=	        $(DLTERM_BOLD)
UNDERLINE=	$(DLTERM_UNDERLINE)
BLINK=	        $(DLTERM_BLINK)
REVERSE=	$(DLTERM_REVERSE)
HIDE=	        $(DLTERM_HIDE)
CLEAR=	        $(DLTERM_CLEAR)
CLRLINE=	$(DLTERM_CLRLINE)

