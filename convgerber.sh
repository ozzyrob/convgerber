#!/bin/bash
# Author: Robert Murphy
# Date: 19 November 2016
# Revision: Initial
# Description:
# Quick and dirty method of converting autotrax gerber file
# to format recognised by FlatCAM
# To do:
# Parse Protel .MAT (Gerber Aperture Match List) to create definitions
# Parse Protel NC drill file to place drill guides in pads
# Add commandline options for src file name & drill guide size

# Name of source gerber file
SRC_FILE=ESP-TEST.GBL

# Temporary file
TMP_FILE=tmp.conv

# Name of converted file
DEST_FILE=esp-test-bcu.gblx


# Save original autotrax gerber file
cp $SRC_FILE $TMP_FILE

# Remove Hex 0x08 from file
sed -i 's/\x08//g' $TMP_FILE

# Remove whitespce 
sed -i 's/[[:blank:]]//g' $TMP_FILE  

# Remove DOS CR
sed -i 's/\r//g' $TMP_FILE

# Remove NEWLINE
sed -i ':a;N;$!ba;s/\n//g' $TMP_FILE

# Change "*" to "*\n" 
sed -i 's/*/*\n/g' $TMP_FILE 

# Generate new file with a prologue
# this is specific to my set up
# look at STANDARD.APT and convert old definitions
# to new definitions
cat << EOF >$DEST_FILE
G04 #@ TF.FileFunction,Copper,L2,Bot,Signal*
%FSLAX23Y23*%
G04 Gerber Fmt 2.3, Leading zero omitted, Abs format (unit inch)*
G04 Created by R.Murphy based on KiCad (PCBNEW 4.0.0-stable) 11-11-2016*
%MOIN*%
G01*
G04 APERTURE LIST*
%ADD11C,0.040*%
%ADD12R,0.010X0.010*%
%ADD13C,0.010*%
%ADD14C,0.012*%
%ADD15C,0.015*%
%ADD16R,0.020X0.020*%
%ADD17C,0.020*%
%ADD18C,0.025*%
%ADD19C,0.030*%
%ADD20R,0.050X0.050*%
%ADD21C,0.050*%
%ADD22R,0.062X0.062*%
%ADD23C,0.062*%
%ADD24C,0.070*%
%ADD25C,0.075*%
%ADD26C,0.085*%
%ADD27C,0.100*%
%ADD28C,0.110*%
%ADD29C,0.125*%
%ADD30C,0.150*%
%ADD31C,0.200*%
%ADD32C,0.250*%
%ADD33P,0.070X8*%
%ADD34P,0.100X8*%
%ADD35C,0.005*%
%ADD36R,0.005X0.005*%
%ADD37R,0.030X0.030*% 
%ADD38C,0.001*%
%ADD39C,0.004*%
%ADD40R,0.025X0.025*%
G04 APERTURE END LIST*
EOF

# Write converted format to new format file
cat $TMP_FILE >> $DEST_FILE

# delete temporary file
rm $TMP_FILE
