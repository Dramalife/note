OUTH=
OUTF=.source.list


default: generate

generate:
	make .output MIRROR_URL="mirrors.ustc.edu.cn"
	make .output MIRROR_URL="mirrors.tuna.tsinghua.edu.cn"

clean:
	-mv -fv ./*$(OUTF) /tmp

.output:
	@echo \
	"# See http://help.ubuntu.com/community/UpgradeNotes for how to upgrade to\n"\
	"# newer versions of the distribution.\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic main restricted\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic main restricted\n"\
	"\n"\
	"## Major bug fix updates produced after the final release of the\n"\
	"## distribution.\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic-updates main restricted\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic-updates main restricted\n"\
	"\n"\
	"## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu\n"\
	"## team. Also, please note that software in universe WILL NOT receive any\n"\
	"## review or updates from the Ubuntu security team.\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic universe\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic universe\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic-updates universe\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic-updates universe\n"\
	"\n"\
	"## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu\n"\
	"## team, and may not be under a free licence. Please satisfy yourself as to\n"\
	"## your rights to use the software. Also, please note that software in\n"\
	"## multiverse WILL NOT receive any review or updates from the Ubuntu\n"\
	"## security team.\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic multiverse\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic multiverse\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic-updates multiverse\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic-updates multiverse\n"\
	"\n"\
	"## N.B. software from this repository may not have been tested as\n"\
	"## extensively as that contained in the main release, although it includes\n"\
	"## newer versions of some applications which may provide useful features.\n"\
	"## Also, please note that software in backports WILL NOT receive any review\n"\
	"## or updates from the Ubuntu security team.\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic-backports main restricted universe multiverse\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic-backports main restricted universe multiverse\n"\
	"\n"\
	"## Uncomment the following two lines to add software from Canonical's\n"\
	"## 'partner' repository.\n"\
	"## This software is not part of Ubuntu, but is offered by Canonical and the\n"\
	"## respective vendors as a service to Ubuntu users.\n"\
	"deb http://archive.canonical.com/ubuntu bionic partner\n"\
	"deb-src http://archive.canonical.com/ubuntu bionic partner\n"\
	"\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic-security main restricted\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic-security main restricted\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic-security universe\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic-security universe\n"\
	"deb http://$(MIRROR_URL)/ubuntu-ports/ bionic-security multiverse\n"\
	"deb-src http://$(MIRROR_URL)/ubuntu-ports/ bionic-security multiverse"\
	> $(OUTH)$(MIRROR_URL)$(OUTF)
	
