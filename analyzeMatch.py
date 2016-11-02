

from os import listdir
from os.path import isfile, join
import re
import numpy as np
#import matplotlib.pyplot as plt

class Result():
    def __init__ (self,fileName,  chipID, xShift, yShift, zShift, phi, theta, seeing, type):

        self.fileName = fileName

        self.chipID = chipID
        self.xShift = xShift
        self.yShift = yShift
        self.zShift = zShift

        self.phi   = phi
        self.theta = theta

        self.seeing = seeing
        self.type =  type   # Ellipticity, Position agnle, or PSF

        self.paa_simu_List = []
        self.paa_data_List = []
        self.psf_simu_List = []
        self.psf_data_List = []

        self.ell_simu_List, self.e1_simu_List, self.e2_simu_List, self.ra_simu_List, self.dec_simu_List = [[]]*5
        self.ell_data_List, self.e1_data_List, self.e2_data_List, self.ra_data_List, self.dec_data_List = [[]]*5


        self.paa_data_mean, self.paa_simu_mean  = 0, 0
        self.paa_data_std, self.paa_simu_std  = 0, 0


        self.psf_data_mean,self.psf_simu_mean = 0, 0
        self.psf_data_std, self.psf_simu_std = 0, 0

        self.ell_data_mean, self.ell_simu_mean = 0, 0
        self.ell_data_std, self.ell_simu_std  = 0, 0




    def update(self):

        if self.type =="PAA":
            f = open(self.fileName, 'r')
            for line in f.readlines():
                temp = line.split()
                self.paa_simu_List.append(float(temp[0]))
                self.paa_data_List.append(float(temp[1]))

            f.close()
            self.paa_data_mean = np.mean(self.paa_data_List)
            self.paa_simu_mean = np.mean(self.paa_simu_List)


        elif self.type=="PSF":
            f = open(self.fileName, 'r')
            for line in f.readlines():
                temp = line.split()
                self.psf_simu_List.append(float(temp[0]))
                self.psf_data_List.append(float(temp[1]))
            f.close()
            self.psf_data_mean = np.mean(self.psf_data_List)
            self.psf_simu_mean = np.mean(self.psf_simu_List)

        elif self.type == "ELL":
            f = open(self.fileName, 'r')
            for line in f.readlines():
                temp = line.split()
                if len(temp)==0:
                    break
                self.ell_simu_List.append(float(temp[0]))
                self.e1_simu_List.append(float(temp[1]))
                self.e2_simu_List.append(float(temp[2]))
                self.ra_simu_List.append(float(temp[3]))
                self.dec_simu_List.append(float(temp[4]))

                self.ell_data_List.append(float(temp[5]))
                self.e1_data_List.append(float(temp[6]))
                self.e2_data_List.append(float(temp[7]))
                self.ra_data_List.append(float(temp[8]))
                self.dec_data_List.append(float(temp[9]))
            f.close()
            self.ell_data_mean = np.mean(self.ell_data_List)
            self.ell_simu_mean = np.mean(self.ell_simu_List)





def readAll(fileNameList):
    objList =[]
    for fileName in fileNameList :
        if not fileName.startswith("Images_"):
            continue
        fileName = "output_txt/" + fileName #Images_99954942266_S1_x_-1.0_y_0_z_0.005_phi_0_psi_0.0_theta_0.0_seeing_0.3.fits_PAA_Simu.txt
        m = re.match(".+Images_(.+)_(.+)_x_(.+)_y_(.+)_z_(.+)_phi_(.+)_psi_(.+)_theta_(.+)_seeing_(.+).fits_(.+)_(.+).txt", fileName)

        chipID = m.group(2)
        xShift = float(m.group(3))
        yShift = float(m.group(4))
        zShift = float(m.group(5))
        phi = float(m.group(6))
        psi = float(m.group(7))
        theta = float(m.group(8))
        seeing = float(m.group(9))
        type = m.group(10)


        obj = Result(fileName, chipID, xShift, yShift, zShift, phi, theta, seeing, type)

        obj.update()
        objList.append(obj)

    return objList



def buildObjDict(objList):
    # build a dictionary contains {(x, y, z, phi, theta, seeing): objList }
    objDict = {}
    for obj in objList:
        key = (obj.xShift,obj.yShift, obj.zShift, obj.phi, obj.theta, obj.seeing)
        if key not in objDict:
            objDict[key] = []

        objDict[key].append(obj)


    return objDict

def getChi2(objDict) :
    # objList include 5 chips:  N1, N4, N7, N22, S22
    newDict = {}
    for key, valList in objDict.iteritems():
        if len(valList) == 18:
            diff_PSF = 0
            diff_ELL = 0
            diff_PAA = 0
            coef_PSF = 1
            coef_ELL = 1
            coef_PAA = 1


            mean_ELL = 0 

            for obj in valList:
                if obj.psf_data_mean > 0:
                    coef_PSF =1/ (obj.psf_data_mean)
                if obj.ell_data_mean > 0:
                    coef_ELL = 1; #1/ (obj.ell_data_mean)
                if obj.paa_data_mean > 0:
                    coef_PAA =1/ (obj.paa_data_mean)

                diff_PSF += coef_PSF * (obj.psf_data_mean - obj.psf_simu_mean) **2
                diff_ELL += coef_ELL * (obj.ell_data_mean - obj.ell_simu_mean) **2
                diff_PAA += coef_PAA * (obj.paa_data_mean - obj.paa_simu_mean) **2


            newDict[key] = (diff_PSF,  diff_ELL,  diff_PAA)

    return newDict


def getChi2_large(objDict) :
    # objList include 5 chips:  N1, N4, N7, N22, S22
    newDict = {}

    

    for key, valList in objDict.iteritems():
        print key
        if len(valList) == 18:   # include 6 chips
            diff_PSF = 0
            diff_ELL = 0
            diff_PAA = 0
            coef_PSF = 1
            coef_ELL = 1
            coef_PAA = 1
            for obj in valList:
                if len(obj.psf_simu_List) == len(obj.psf_data_List):
                    for i in range(len(obj.psf_simu_List)):
                        if obj.psf_data_List[i] > 0:
                            diff_PSF += (obj.psf_simu_List[i] - obj.psf_data_List[i]) **2 / (0.1*0.1) #obj.psf_data_List[i]
                    for i in range(len(obj.ell_simu_List)):
                        if obj.ell_data_List[i] > 0:
                            diff_ELL += (obj.ell_simu_List[i] - obj.ell_data_List[i]) **2 / (0.03*0.03) #obj.ell_data_List[i]
                    for i in range(len(obj.paa_simu_List)):
                        if obj.paa_data_List[i] > 0:
                            diff_PAA += (obj.paa_simu_List[i] - obj.paa_data_List[i]) **2 / obj.paa_data_List[i]


            newDict[key] = (diff_PSF,  diff_ELL,  diff_PAA)

    return newDict

def writeResult(newDict, outFileName):
    f = open(outFileName, 'w')
    for key, value in newDict.iteritems():
        if not np.isnan(value[0]) and not np.isnan(value[1]) and not np.isnan(value[2]):
            for i in range(len(key)):
                f.write(str(key[i]) + "\t")
            for j in range(len(value)):
                f.write(str(value[j])+ "\t")
            f.write(str(value[0]+value[1]))
            f.write("\n")

    f.close()


def plotDict(outputFileName):
    x = np.arange(0.0, 2.0, 0.25)
    y = np.arange(0.0, 2.0, 0.25)
    seeing = []
    see = 1.35
    print x, y
    X, Y = np.meshgrid(x, y)


    f = open(outputFileName, 'r')
    tempDICT = {}
    max_ell = []
    for line in f.readlines():
        temp = line.split()
        if float(temp[5])== see:
            tempDICT[(float(temp[0]),float(temp[1]) )] = float(temp[7])
            max_ell.append(float(temp[7]))
        seeing.append(float(temp[5]))


    Z = np.copy(X)




    for i in range(len(X)):
        for j in range(len(X[i])):
            if (X[i][j], Y[i][j]) in tempDICT:
                Z[i][j] = tempDICT[(X[i][j], Y[i][j])]
            else:
                Z[i][j] = max(max_ell)

    print Z

    fig = plt.imshow(Z, interpolation='none', vmin=0, vmax= 6.0e-6)
    plt.colorbar(orientation='vertical')

    plt.title("seeing = " + str(see))
    #plt.axis('off')

    fig.axes.get_xaxis().set_visible(False)
    fig.axes.get_yaxis().set_visible(False)
    #plt.axis('equal')
    plt.xlabel("X")
    plt.ylabel("Y")
    f.close()

    plt.show()
    #plt.savefig("seeing_"+str(see)+".png", pad_inches = 0)







def findMin(newDict, col):
    # col = 0 indictates psf
    # col = 1 indicates ellipticity
    # col = 2 indicates position angle

    min_value = 100000
    min_index = 0
    for key, value in newDict.iteritems():
        if value[col]<min_value and key[5] == 0.65:
            min_value = value[col]
            min_index = key
    return min_index, min_value

def main():
    #CHIPS = ['S1', 'N7', 'S4', 'N4', 'N29', 'S31']
    mypath = "output_txt"
    fileNameList = [f for f in listdir(mypath) if isfile(join(mypath, f))]

    objList = readAll(fileNameList)

    objDict = buildObjDict(objList)

    #newDict = getChi2_large(objDict)
    newDict = getChi2(objDict)
    writeResult(newDict, "new_output_ell_mean.txt")


    min_index, min_value  = findMin(newDict, col = 0)
    #print min_index, newDict[min_index]


    #plotDict("output.txt")


if __name__ == "__main__":
    main()
