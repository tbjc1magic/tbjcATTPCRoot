# tbjcATTPCroot

########################
##### instruction ######
########################

Root version > 6.xx is required for this program

to build:
mkdir build
cd build
cmake ..

for multiprocess running, use mult.py and change the path for the data resources and data output path.

#######################
##### description #####
#######################

this program fake up the TClonesArray in the root and FairRootManager, FairTask, FairRun, FairRunAna and also FairParset from the FairRoot and FairSoft. So it loses the ability to visualize the trajectories in FairRoot.

#####################
##### test ##########
#####################

This problem has been tested under local workstations, google cloud Ubuntu images, and Crcfe01, Canopus HPC node. 

########################
##### responsibility ###
########################

This project reuses most codes from the one by Yassid, https://github.com/ATTPC/ATTPCROOT. I will not be liable for the code maintainence, or any bugs.
