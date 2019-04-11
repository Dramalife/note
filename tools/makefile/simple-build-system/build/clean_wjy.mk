




OUTAPPEXAM = $(OUTAPP)/appexam
APPEXAMDIR = $(APPDIR)/example
APPINSTDIR = $(IMGRFS)/usr/local/bin

cleanhaha:
	@$(ECHO) -n "clean"
	@$(RM) $(OUTAPPEXAM)
	#@$(RM) $(APPEXAMDIR)
	#@$(MAKE) -C $(OUTAPPEXAM)
	@$(RM)  $(APPINSTDIR)
	@$(RM)  $(APPINSTDIR)/syjc-app-exam
	@$(ECHO) "Done"

#add more applications here
