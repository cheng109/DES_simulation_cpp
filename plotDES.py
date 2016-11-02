__author__ = 'cheng109'
import matplotlib.pyplot as plt
import matplotlib
import os.path
import math
import numpy as np

def extractColumn(fileName, column):
    list = []
    if os.path.isfile(fileName):
        txtFile = open(fileName, 'r')

        for line in txtFile.readlines():
            temp = line.split()
            list.append(float(temp[column]))

    return list



def plotMultCHIPS2(CHIPS, prefix):

    axS1 = plt.subplot2grid((14,14), (6, 0), colspan=2)
    axS2 = plt.subplot2grid((14,14), (6, 2), colspan=2)
    axS3 = plt.subplot2grid((14,14), (6, 4), colspan=2)
    axS4 = plt.subplot2grid((14,14), (6, 6), colspan=2)
    axS5 = plt.subplot2grid((14,14), (6, 8), colspan=2)
    axS6 = plt.subplot2grid((14,14), (6, 10), colspan=2)
    axS7 = plt.subplot2grid((14,14), (6, 12), colspan=2)

    axS8 = plt.subplot2grid((14,14), (5, 1), colspan=2)
    axS9 = plt.subplot2grid((14,14), (5, 3), colspan=2)
    axS10 = plt.subplot2grid((14,14), (5, 5), colspan=2)
    axS11 = plt.subplot2grid((14,14), (5, 7), colspan=2)
    axS12 = plt.subplot2grid((14,14), (5, 9), colspan=2)
    axS13 = plt.subplot2grid((14,14), (5, 11), colspan=2)

    axS14 = plt.subplot2grid((14,14), (4, 1), colspan=2)
    axS15 = plt.subplot2grid((14,14), (4, 3), colspan=2)
    axS16 = plt.subplot2grid((14,14), (4, 5), colspan=2)
    axS17 = plt.subplot2grid((14,14), (4, 7), colspan=2)
    axS18 = plt.subplot2grid((14,14), (4, 9), colspan=2)
    axS19 = plt.subplot2grid((14,14), (4, 11), colspan=2)

    axS20 = plt.subplot2grid((14,14), (3, 2), colspan=2)
    axS21 = plt.subplot2grid((14,14), (3, 4), colspan=2)
    axS22 = plt.subplot2grid((14,14), (3, 6), colspan=2)
    axS23 = plt.subplot2grid((14,14), (3, 8), colspan=2)
    axS24 = plt.subplot2grid((14,14), (3, 10), colspan=2)

    axS25 = plt.subplot2grid((14,14), (2, 3), colspan=2)
    axS26 = plt.subplot2grid((14,14), (2, 5), colspan=2)
    axS27 = plt.subplot2grid((14,14), (2, 7), colspan=2)
    axS28 = plt.subplot2grid((14,14), (2, 9), colspan=2)

    axS29 = plt.subplot2grid((14,14), (1, 4), colspan=2)
    axS30 = plt.subplot2grid((14,14), (1, 6), colspan=2)
    axS31 = plt.subplot2grid((14,14), (1, 8), colspan=2)

    #  N parts:
    axN1 = plt.subplot2grid((14,14), (7, 0), colspan=2)
    axN2 = plt.subplot2grid((14,14), (7, 2), colspan=2)
    axN3 = plt.subplot2grid((14,14), (7, 4), colspan=2)
    axN4 = plt.subplot2grid((14,14), (7, 6), colspan=2)
    axN5 = plt.subplot2grid((14,14), (7, 8), colspan=2)
    axN6 = plt.subplot2grid((14,14), (7, 10), colspan=2)
    axN7 = plt.subplot2grid((14,14), (7, 12), colspan=2)

    axN8 = plt.subplot2grid((14,14), (8, 1), colspan=2)
    axN9 = plt.subplot2grid((14,14), (8, 3), colspan=2)
    axN10 = plt.subplot2grid((14,14), (8, 5), colspan=2)
    axN11 = plt.subplot2grid((14,14), (8, 7), colspan=2)
    axN12 = plt.subplot2grid((14,14), (8, 9), colspan=2)
    axN13 = plt.subplot2grid((14,14), (8, 11), colspan=2)


    axN14 = plt.subplot2grid((14,14), (9, 1), colspan=2)
    axN15 = plt.subplot2grid((14,14), (9, 3), colspan=2)
    axN16 = plt.subplot2grid((14,14), (9, 5), colspan=2)
    axN17 = plt.subplot2grid((14,14), (9, 7), colspan=2)
    axN18 = plt.subplot2grid((14,14), (9, 9), colspan=2)
    axN19 = plt.subplot2grid((14,14), (9, 11), colspan=2)

    axN20 = plt.subplot2grid((14,14), (10, 2), colspan=2)
    axN21 = plt.subplot2grid((14,14), (10, 4), colspan=2)
    axN22 = plt.subplot2grid((14,14), (10, 6), colspan=2)
    axN23 = plt.subplot2grid((14,14), (10, 8), colspan=2)
    axN24 = plt.subplot2grid((14,14), (10, 10), colspan=2)

    axN25 = plt.subplot2grid((14,14), (11, 3), colspan=2)
    axN26 = plt.subplot2grid((14,14), (11, 5), colspan=2)
    axN27 = plt.subplot2grid((14,14), (11, 7), colspan=2)
    axN28 = plt.subplot2grid((14,14), (11, 9), colspan=2)

    axN29 = plt.subplot2grid((14,14), (12, 4), colspan=2)
    axN30 = plt.subplot2grid((14,14), (12, 6), colspan=2)
    axN31 = plt.subplot2grid((14,14), (12, 8), colspan=2)

    axN30.set_axis_bgcolor('grey')
    axS7.set_axis_bgcolor('grey')
    #axS1.axes.get_yaxis().set_visible(False)
    #axS1.axes.get_xaxis().set_visible(False)


    axList = [axS1, axS2,axS3, axS4, axS5, axS6, axS7, axS8,axS9, axS10, axS11, axS12,axS13, axS14,axS15,
              axS16, axS17, axS18, axS19, axS20,axS21, axS22, axS23, axS24,axS25, axS26 ,axS27, axS28, axS29, axS30, axS31,
              axN1, axN2,axN3, axN4, axN5, axN6, axN7, axN8,axN9, axN10, axN11, axN12,axN13, axN14,axN15,
              axN16, axN17, axN18, axN19, axN20,axN21, axN22, axN23, axN24,axN25, axN26 ,axN27, axN28, axN29, axN30, axN31]

    removeAxis(axList)

    All_CHIPS = ['S1', 'S2','S3', 'S4', 'S5', 'S6', 'S7', 'S8','S9', 'S10', 'S11', 'S12','S13', 'S14','S15',
              'S16', 'S17', 'S18', 'S19', 'S20','S21', 'S22', 'S23', 'S24','S25', 'S26','S27', 'S28', 'S29', 'S30', 'S31',
              'N1', 'N2','N3', 'N4', 'N5', 'N6', 'N7', 'N8','N9', 'N10', 'N11', 'N12','N13', 'N14','N15',
              'N16', 'N17', 'N18', 'N19', 'N20','N21', 'N22', 'N23', 'N24','N25', 'N26','N27', 'N28', 'N29', 'N30', 'N31'] 

    plotDictionary = dict(zip(All_CHIPS, axList))

    CHIPS = All_CHIPS

    numEllBins = 20
    numPSFBins = 30
    numPAABins = 30

    minEll = 0.0
    maxEll = 0.20

    minPSF = 2.0
    maxPSF = 3.5

    minPAA = -200
    maxPAA = 200

    ellBins= []
    psfBins= []
    paaBins = []


    for i in range(numEllBins):
        ellBins.append(i*(maxEll-minEll)/numEllBins)
    for i in range(numPSFBins):
        psfBins.append(minPSF + i*(maxPSF-minPSF)/numPSFBins)
    for i in range(numPAABins):
        paaBins.append(minPAA + i*(maxPAA-minPAA)/numPAABins)

    for chip in CHIPS :

        # data_PSF_file = prefix + "PSF_Data_" + chip + ".txt"
        # data_ELL_file = prefix +"ELL_Data_"  + chip + ".txt"
        # data_PAA_file = prefix +"PAA_Data_"  + chip + ".txt"


        # sim_PSF_file  = prefix +"PSF_Simu_"   + chip + ".txt"
        # sim_ELL_file  = prefix +"ELL_Simu_"   + chip + ".txt"
        # sim_PAA_file  = prefix +"PAA_Simu_"   + chip + ".txt"

        DIR = "simuCatalog/"
        txtFileName = DIR  + chip + "_output_test.txt"
        if (not os.path.isfile(txtFileName)) : 
            continue
        ellData = extractColumn(txtFileName, column = 0)
        ellSimu = extractColumn(txtFileName, column = 8)


        # psfData = txtToList(data_PSF_file)
        # ellData = txtToList(data_ELL_file)
        # paaData = txtToList(data_PAA_file)

        # psfSim  = txtToList(sim_PSF_file)
        # ellSim  = txtToList(sim_ELL_file)
        # paaSim  = txtToList(sim_PAA_file)



        ax = plotDictionary[chip]

        ax.hist(ellData, bins = ellBins,  normed=1, color='blue',  label = "Ell_Data",  alpha=1.0)
        ax.hist(ellSimu,  bins = ellBins,  normed=1, color='green', label = "Ell_Sim",  alpha=0.5)

    #axS30.legend()
    #plt.savefig("full_map.pdf", format='pdf')
    plt.show()


def removeAxis(axList):
    for ax in axList:
        ax.axes.get_xaxis().set_visible(False)
        ax.axes.get_yaxis().set_visible(False)


def plotMagDiff(mp):
    f, ((ax1), (ax2)) = plt.subplots(2, 1)  
    data_mag = mp["data_mag"]
    simu_mag = mp["simu_mag"]

    mag_diff = []
    for i in range(len(data_mag)): 
        mag_diff.append(simu_mag[i]-data_mag[i])

    ax1.plot(simu_mag, data_mag) 
    ax2.plot(mag_diff, data_mag) 

    plt.show()

def plotPositionDiff(mp):
    # of=open("position.txt", 'w')
    # count = 0
    # if plot==True:
    f, ((ax1, ax3), (ax2, ax4)) = plt.subplots(2, 2) #, sharex='col', sharey='row')

    data_xcenter = mp["data_xcenter"] 
    data_ycenter = mp["data_ycenter"]
    simu_xcenter = mp["simu_xcenter"]
    simu_ycenter = mp["simu_ycenter"]

    dxList = []
    dyList = []
    xcenter = []
    ycenter = []
    for i in range(len(data_xcenter)): 
        xcenter.append(data_xcenter[i])
        ycenter.append(data_ycenter[i])
        dxList.append(simu_xcenter[i] - data_xcenter[i])
        dyList.append(simu_ycenter[i] - data_ycenter[i])

    #######################  show postion matching function  #######################
    slopeXX, interceptXX = np.polyfit(xcenter, dxList, 1)
    slopeXY, interceptXY = np.polyfit(ycenter, dxList, 1)
    slopeYX, interceptYX = np.polyfit(xcenter, dyList, 1)
    slopeYY, interceptYY = np.polyfit(ycenter, dyList, 1)

    print "Dx VS X function:   Dx = ", slopeXX, "*X + ", interceptXX
    print "Dx VS Y function:   Dx = ", slopeXY, "*Y + ", interceptXY
    print "Dy VS X function:   Dy = ", slopeYX, "*Y + ", interceptYX
    print "Dy VS Y function:   Dy = ", slopeYY, "*Y + ", interceptYY

    meanDx = np.mean(dxList)
    meanDy = np.mean(dyList)
    print "Mean(dx) = ", meanDx, " std(dx) = ", np.std(dxList)
    print "Mean(dy) = ", meanDy, " std(dy) = ", np.std(dyList)

  
    angle = math.degrees(math.atan(slopeXY))
    print "Rotation Angle: ", math.degrees(math.atan(slopeXY)), " degree"
    #################################################################################


 
    ax1.plot(xcenter, dxList, 'r.')
    ax2.plot(xcenter, dyList, 'r.')
    ax3.plot(ycenter, dxList, 'r.')
    ax4.plot(ycenter, dyList, 'r.')


    lim = 1
    ax1.set_ylim([-lim, lim])
    ax2.set_ylim([-lim, lim])
    ax3.set_ylim([-lim, lim])
    ax4.set_ylim([-lim, lim])




    ax1.set_xlabel("X  (pixels)")
    ax1.set_ylabel("dX (pixels)")
    ax2.set_xlabel("X  (pixels)")
    ax2.set_ylabel("dY (pixels)")
    ax3.set_xlabel("Y  (pixels)")
    ax3.set_ylabel("dX (pixels)")
    ax4.set_xlabel("Y  (pixels)")
    ax4.set_ylabel("dY (pixels)")

    plt.show()
        #f.savefig(chip + "position.pdf")

   
def parseText(fileName) : 
    data_e, data_pa, data_e1, data_e2, data_xcenter, data_ycenter, data_xworld, data_yworld, data_mag = ([] for i in range(8))
    simu_e, simu_pa, simu_e1, simu_e2, simu_xcenter, simu_ycenter, simu_xworld, simu_yworld, simu_mag = ([] for i in range(8))


    f = open(fileName, 'r')
    for line in f.readlines():
        temp = line.split()
        data_e.         append(float(temp[0]))
        data_pa.        append(float(temp[1]))
        data_e1.        append(float(temp[2]))
        data_e2.        append(float(temp[3]))
        data_xcenter.   append(float(temp[4]))
        data_ycenter.   append(float(temp[5]))
        data_xworld.    append(float(temp[6]))
        data_yworld.    append(float(temp[7]))
        data_mag.       append(float(temp[8]))


        last = 9
        simu_e.         append(float(temp[last+0]))
        simu_pa.        append(float(temp[last+1]))
        simu_e1.        append(float(temp[last+2]))
        simu_e2.        append(float(temp[last+3]))
        simu_xcenter.   append(float(temp[last+4]))
        simu_ycenter.   append(float(temp[last+5]))
        simu_xworld.    append(float(temp[last+6]))
        simu_yworld.    append(float(temp[last+7]))
        simu_mag.       append(float(temp[last+8]))

    f.close()
    mp = {"data_e"      : data_e,       "data_pa"     : data_pa,      "data_e1"    : data_e1,     "data_e2"     : data_e2, 
          "data_xcenter": data_xcenter, "data_ycenter": data_ycenter, "data_xworld": data_xworld, "data_yworld" : data_yworld, \
          "data_mag"    : data_mag, \
          "simu_e"      : simu_e,       "simu_pa"     : simu_pa,      "simu_e1"    : simu_e1,     "simu_e2"     : simu_e2, 
          "simu_xcenter": simu_xcenter, "simu_ycenter": simu_ycenter, "simu_xworld": simu_xworld, "simu_yworld": simu_yworld, \
          "simu_mag"    : simu_mag, }
    return mp


def main():
    #parseConfigure("conf.txt")
    # shift = {"x": -1.0, "y": -1.0, "z": 0.0}
    # tilt = {"phi": 0.0, "psi": 42.0, "theta": 0}
    # DIR  = "real_temp/output_txt/"
    # prefix = DIR + "output_" + "_x_" + str(shift["x"]) + "_y_" + str(shift["y"]) + "_z_" +str(shift["z"]) +  "_phi_" + str(tilt["phi"])+ "_psi_" + str(tilt["psi"]) + "_theta_" + str(tilt["theta"]) + "_"

    # prefix = ""
    # CHIPS = []
    # plotMultCHIPS2(CHIPS, prefix)
    mp  = parseText("N4_output_test.txt")

    plotPositionDiff(mp)
    #plotMagDiff(mp)


if __name__=='__main__':
    main()



