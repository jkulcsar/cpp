#!/bin/ksh

SYBASE_PASSWORD=rbc2000
export SYBASE_PASSWORD

config=`config.guess`
op_sys=`uname -sr`
case $op_sys in
    HP-UX* )

        ;;

    SunOS* )
        ENVIRONMENT=DEV
        export ENVIRONMENT 

        #### Enable core dumps into current directory ####
        ## core is called core.<executable_name>.process-ID
        /usr/bin/coreadm -p core.%f.%p $$

        #### C Compiler ####
        CC=cc
        #ANSI_CFLAGS=
        #MISC_CFLAGS=
        #CFLAGS="$ANSI_CFLAGS $MISC_CFLAGS"
        export CC 

        #### C++ Compiler ####
        if [ -d /opt/SUNWspro ]; then
            CXX=CC
            #ANSI_CXXFLAGS=
            #MISC_CXXFLAGS=
            #CXXFLAGS="$ANSI_CXXFLAGS $MISC_CXXFLAGS"
            PATH=/opt/SUNWspro/bin:$PATH
            export CXX 
        fi
        
        ##### GUTS_HOME #####
        if [ -d /usr/rbc ]; then
            GUTS_HOME=/usr/rbc
            RATS_HOME=$GUTS_HOME/ra
            RBC_LIB_DIR=$GUTS_HOME/$config/lib
            export GUTS_HOME RATS_HOME RBC_LIB_DIR
        fi

        ##### MQ Series #####
        if [ -d /opt/mqm ]; then
            MQ_HOME=/opt/mqm
            MQCCSID=819
            MQSERVER="TOTD1/TCP/192.64.161.164"
            export MQ_HOME MQCCSID MQSERVER
            setEnv LD_LIBRARY_PATH $MQ_HOME/lib
        fi

        ##### Java #####
        if [ -d /usr/j2se ]; then
            JAVA_HOME=/usr/j2se
            export JAVA_HOME
            setPaths app $JAVA_HOME/bin
        elif [ -d /opt/java ]; then
            JAVA_HOME=/opt/java/jre
            export JAVA_HOME
            setPaths app $JAVA_HOME/bin
        fi
 
        ##### MOTIF and X #####
        MOTIF_INC_DIR=/usr/dt/include
        MOTIF_LIB_DIR=/usr/dt/lib
        X_INC_DIR=/usr/openwin/include
        X_LIB_DIR=/usr/openwin/lib
        export MOTIF_INC_DIR MOTIF_LIB_DIR X_INC_DIR X_LIB_DIR

        ##### Rendezvous #####
        if [ -d /usr/tss_root/tibrv_7.5.2 ]; then
            RV_ROOT=/usr/tss_root/tibrv_7.5.2
            export RV_ROOT
	    	setPaths app $RV_ROOT/bin
            setEnv LD_LIBRARY_PATH $RV_ROOT/lib
            setEnv CLASSPATH $RV_ROOT/lib/tibrvj.jar
        fi 
        
	##### RFA #####
        if [ -f /opt/Reuters/RFA_ROOT ]; then
            . /opt/Reuters/RFA_ROOT
            export RFA_ROOT
            setEnv LD_LIBRARY_PATH $RFA_ROOT/lib
		elif [ -d /u/Reuters ]; then
			RFA_ROOT=/u/Reuters/rfa6.0.0.E3
            export RFA_ROOT
            setEnv LD_LIBRARY_PATH $RFA_ROOT/Libs/SOL10_SPARC_32_SS10
        fi 
            
        ##### SYBASE #####
        if [ -d /opt/sybase12.5 ]; then
            SYBASE=/opt/sybase12.5
            SYBASE_OC=$SYBASE/OCS-12_5
            export SYBASE SYBASE_OC
            setEnv LD_LIBRARY_PATH $SYBASE_OC/lib
            setPaths app $SYBASE_OC/bin
        fi 

        ##### UIM/X #####
        if [ -d /opt/uimx3.0 ]; then
            UIMX_HOME=/opt/uimx3.0
            export UIMX_HOME
	    setPaths app $UIMX_HOME/bin
        fi 
        
        MANPATH=$MANPATH:$GUTS_HOME/man
        export MANPATH
        export LD_LIBRARY_PATH
        ;;

    Linux* )
        ENVIRONMENT=DEV
        export ENVIRONMENT 

        #### C Compiler ####
        CC=gcc
        ANSI_CFLAGS=-ansi
        MISC_CFLAGS=-Wall
        CFLAGS="$ANSI_CFLAGS $MISC_CFLAGS"
        export ANSI_CFLAGS CC CFLAGS MISC_CFLAGS 

        #### C++ Compiler ####
        CXX=g++
        ANSI_CXXFLAGS=-ansi
        MISC_CXXFLAGS=-Wall
        CXXFLAGS="$ANSI_CXXFLAGS $MISC_CXXFLAGS"
        export ANSI_CXXFLAGS CXX CXXFLAGS MISC_CXXFLAGS 
        
        ##### GUTS_HOME #####
        if [ -d /usr/rbc ]; then
            GUTS_HOME=/usr/rbc/rbc_dev
            RATS_HOME=$GUTS_HOME/ra
            RBC_LIB_DIR=$GUTS_HOME/$config/lib
            export GUTS_HOME RATS_HOME RBC_LIB_DIR
        fi

        ##### MQ Series #####
        if [ -d /opt/mqm ]; then
            MQ_HOME=/opt/mqm
            MQCCSID=819
            MQSERVER="TOTD1/TCP/192.64.161.164"
            export MQ_HOME MQCCSID MQSERVER
            setEnv LD_LIBRARY_PATH $MQ_HOME/lib
        fi

        ##### MOTIF and X #####
        MOTIF_INC_DIR=/usr/X11R6/include
        MOTIF_LIB_DIR=/usr/X11R6/lib
        X_INC_DIR=/usr/X11R6/include
        X_LIB_DIR=/usr/X11R6/lib
        export MOTIF_INC_DIR MOTIF_LIB_DIR X_INC_DIR X_LIB_DIR

        ##### Rendezvous #####
        if [ -d /usr/tibco/tibrv ]; then
            RV_ROOT=/usr/tibco/tibrv
            export RV_ROOT
	    setPaths app $RV_ROOT/bin
            setEnv LD_LIBRARY_PATH $RV_ROOT/lib
            setEnv CLASSPATH $RV_ROOT/lib/tibrvj.jar
        fi 
        
		##### RFA #####
        if [ -f /opt/Reuters/RFA_ROOT ]; then
            . /opt/Reuters/RFA_ROOT
            export RFA_ROOT
            setEnv LD_LIBRARY_PATH $RFA_ROOT/lib
        fi 
            
        ##### SYBASE #####
        if [ -d /opt/sybase12.5 ]; then
            SYBASE=/opt/sybase12.5
            SYBASE_OC=$SYBASE/OCS-12_5
            export SYBASE SYBASE_OC
            setEnv LD_LIBRARY_PATH $SYBASE_OC/lib
            setPaths app $SYBASE_OC/bin
        fi 

        ##### UIM/X #####
        if [ -d /opt/uimx3.0 ]; then
            UIMX_HOME=/opt/uimx3.0
            export UIMX_HOME
	    setPaths app $UIMX_HOME/bin
        fi 
        
        MANPATH=$MANPATH:$GUTS_HOME/man
        export MANPATH
        export LD_LIBRARY_PATH
        ;;
    * )
        ;;
esac




