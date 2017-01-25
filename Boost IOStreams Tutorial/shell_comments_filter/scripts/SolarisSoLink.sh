#!/bin/ksh
echo "Shared Object Link Creation Start."
#echo " "
#echo "Creating links for shared objects for SOL10_X64_32_SS10."
#echo " "

#cd Libs/SOL10_X64_32_SS10
#ln -s libRFA_Common.so.6 libRFA_Common.so
#ln -s libRFA_Config.so.6 libRFA_Config.so
#ln -s libRFA_Data.so.6 libRFA_Data.so
#ln -s libRFA_Message.so.6 libRFA_Message.so
#ln -s libRFA_Logger.so.6 libRFA_Logger.so
#ln -s libRFA_Adapter.so.6 libRFA_Adapter.so
#ln -s libRFA_Connections.so.6 libRFA_Connections.so
#ln -s libRFA_RSSL_Adapter.so.6 libRFA_RSSL_Adapter.so
#ln -s libRFA_RSSL_Prov_Adapter.so.6 libRFA_RSSL_Prov_Adapter.so
#ln -s libRFA_SASS3_Adapter.so.6 libRFA_SASS3_Adapter.so
#ln -s libRFA_SSLED_Adapter.so.6 libRFA_SSLED_Adapter.so
#ln -s libRFA_SSLED_MP_Adapter.so.6 libRFA_SSLED_MP_Adapter.so
#ln -s libRFA_STIC_Adapter.so.6 libRFA_STIC_Adapter.so
#ln -s libRFA_SessionLayer.so.6 libRFA_SessionLayer.so
#cd ../..

echo "Creating links for shared objects for SOL10_SPARC_32_SS10."
echo " "

cd Libs/SOL10_SPARC_32_SS10
ln -s libRFA_Common.so.6 libRFA_Common.so
ln -s libRFA_Config.so.6 libRFA_Config.so
ln -s libRFA_Data.so.6 libRFA_Data.so
ln -s libRFA_Message.so.6 libRFA_Message.so
ln -s libRFA_Logger.so.6 libRFA_Logger.so
ln -s libRFA_Adapter.so.6 libRFA_Adapter.so
ln -s libRFA_Connections.so.6 libRFA_Connections.so
ln -s libRFA_RSSL_Adapter.so.6 libRFA_RSSL_Adapter.so
ln -s libRFA_RSSL_Prov_Adapter.so.6 libRFA_RSSL_Prov_Adapter.so
ln -s libRFA_SASS3_Adapter.so.6 libRFA_SASS3_Adapter.so
ln -s libRFA_SSLED_Adapter.so.6 libRFA_SSLED_Adapter.so
ln -s libRFA_SSLED_MP_Adapter.so.6 libRFA_SSLED_MP_Adapter.so
ln -s libRFA_STIC_Adapter.so.6 libRFA_STIC_Adapter.so
ln -s libRFA_SessionLayer.so.6 libRFA_SessionLayer.so
cd ../..

echo "Shared Object Link Creation Completed."
echo " "
