# convgerber
Convert Protel Autotrax gerber for use with FlatCAM

The bash script does not have the drill guide import feature or the file checking feature.

convgerber.c

Usage: convgerber -i <input GERBER> -o <output file> [-g <optional drill guide]. [-v] [-h]

	-i <input gerber> : Specifies which file contains the gerber file to convert.
	-g <input DRILL GUIDE> : Specifies which file contains the drill guide gerber to use.
	-o <output file> : specifies which file the converted gerber is to be saved to.

	-v : Display current software version
	-h : Display this help.

Notes:
Additionally a aperture.dat file is required that contains the same definitions in the newer format as the Autotrax STANDARD.APT file. Examples have been included in this repo for download.

To use the supplied aperture files:

1: In your traxplot directory rename STANDARD.APT to STANDARD.BAK thereby preserving your original file.

2: Copy the newer STANDARD.APT to your traxplot directory.

3: Make sure aperture.dat is in the same directory that the files to convert.

Info about the GERBER format is available at:

http://www.artwork.com/gerber/appl2.htm and http://www.artwork.com/gerber/274x/rs274x.htm
