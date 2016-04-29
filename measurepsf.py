##
# @package phosim
## @file phosim
## @brief main script to measurepsf.py
##
## @brief Created by:
## @author Jun Cheng (Purdue)
##
##
## @warning This code is not fully validated
## and not ready for full release.  Please
## treat results with caution.
##
## Requirement:
## python library:  astropy.
##
## Example:
## python measurepsf.py cut_test.fits
##
## This code will return: e1, e2, ellip, pa, flux,rms



from astropy.io import fits
import math
import time 

def readFitsImage(imageName):
    hdulist = fits.open(imageName)
    data =  hdulist[0].data
    hdulist.close()
    return data

def getEllipticity(data):
    size = data.shape
    t1, t2, t3, t4, t5, t6 = (0, )*6

    f=open("data.txt", 'w')
    f.write("[")
    for i in range(size[0]):
        f.write("[")
        for j in range(size[1]):
            f.write(str(data[i][j]))
            if j!=size[1]-1:
                f.write(",")
            t1 += i*j*data[i][j]
            t2 += data[i][j]
            t3 += i*data[i][j]
            t4 += j*data[i][j]
            t5 += i*i*data[i][j]
            t6 += j*j*data[i][j]
        f.write("],")
    f.write("]\n")
    covxy = t1/t2-t3*t4/t2/t2
    resultx = t5/t2-t3*t3/t2/t2
    resulty = t6/t2-t4*t4/t2/t2

    print size[0]; 
    print size[1]; 

    medx = size[0]/2.0
    medy = size[1]/2.0
    alphax = math.sqrt(resultx*2.0)
    alphay = math.sqrt(resulty*2.0)
    alphaxy = covxy*math.sqrt(2.0)

    converge = False
    for trials in range(100):
        t1, t2, t3,t4, t5, t6, t7 = (0,)*7
        print trials
        for i in range(size[0]):
            for j in range(size[1]):
                #try:
                weight = (math.exp(-((i-medx)**2/alphax/alphax-2.0*alphaxy/alphax/alphax/alphay/alphay*(i-medx)*(j-medy)+(j-medy)**2/alphay/alphay)/2.0/(1-(alphaxy/alphax/alphay)**2)))/(2*math.pi*alphax*alphay*math.sqrt(1-(alphaxy/alphax/alphay)**2))
                #except OverflowError:
                #    return 0, 0, 0, 0, 0,  0,0, 0, 0, 0
                #except ZeroDivisionError:
                #    return 0, 0, 0, 0, 0,  0,0, 0, 0, 0
                #except ValueError: 
                #    return 0, 0, 0, 0, 0,  0,0, 0, 0, 0
                t1 += i*j*data[i][j]*weight
                t2 += data[i][j]*weight
                t3 += i*data[i][j]*weight
                t4 += j*data[i][j]*weight
                t5 += i*i*data[i][j]*weight
                t6 += j*j*data[i][j]*weight
                t7 += data[i][j]

        covxy=(t1/t2-t3*t4/t2/t2)
        resultx=(t5/t2-t3*t3/t2/t2)
        resulty=(t6/t2-t4*t4/t2/t2)
        medx=(t3/t2)
        medy=(t4/t2)
        flux=t7

        if (resultx + resulty) < 0:
            break
        rms=math.sqrt(resultx+resulty)

        e1=(resulty-resultx)/(resultx+resulty)
        e2=(2.0*covxy)/(resultx+resulty)

        ellip= math.sqrt(e1**2+e2**2)
        #pa=0.5*math.degrees(math.atan(e2/e1))-90

        real_pa = 0.5* math.degrees(math.atan2(e2, e1))

        pa = 0.5* real_pa - 90
        if resultx<1.0e-6 or resulty<1.0e-6:
            break

        #print resultx, resulty
        if (abs(alphax-math.sqrt(2.0*resultx)) < 1e-6 and abs(alphay-math.sqrt(2.0*resulty)) < 1e-6 and abs(alphaxy-2.0*covxy) < 1e-6) :
            converge = True
            break
        alphax=math.sqrt(resultx*2.0)
        alphay=math.sqrt(resulty*2.0)
        alphaxy=covxy*2.0
    return e1, e2, ellip, pa, real_pa,  flux,rms, converge, alphax, alphay


def main():
    start = time.time()
    imageName = 'measure_PSF_test_back_0.0_e_0.23_PA_130.fits'
    data = readFitsImage(imageName)
    for i in range(data.shape[0]): 
        for j in range(data.shape[1]): 
            data[i][j] -= 0.0

    e1, e2, ellip, pa, real_pa,  flux,rms, converge, alphax, alphay = getEllipticity(data)
    print "e1 = ", e1
    print "e2 = ", e2
    print "e  = ", ellip
    print "Position angle = ", pa
    print "Flux = ", flux
    print "RMS = ", rms
    print "time_elapse: ", time.time() - start  

if __name__=='__main__':
    main()
