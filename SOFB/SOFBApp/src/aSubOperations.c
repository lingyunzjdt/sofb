#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dbAccess.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <waveformRecord.h>
#include <epicsExport.h>
#include <epicsTime.h>
#include <math.h>

static float unitScale=1.0;

/*
static long cellRefParse(aSubRecord *pasub) {
	float *aptr,*bptr;
	char *cptr,*dptr;

	float *vaptr,*vbptr,*vcptr,*vdptr,*veptr,*vfptr;
	float *vgptr,*vhptr,*viptr,*vjptr,*vkptr,*vlptr;
	
	aptr = (float *)pasub->a;
	bptr = (float *)pasub->b;
	cptr = (char *)pasub->c;
	dptr = (float *)pasub->d;

	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;
	vcptr = (float *)pasub->valc;
	vdptr = (float *)pasub->vald;
	veptr = (float *)pasub->vale;
	vfptr = (float *)pasub->valf;

	vgptr = (float *)pasub->vala;
	vhptr = (float *)pasub->valb;
	vptr = (float *)pasub->valc;
	vdptr = (float *)pasub->vald;
	veptr = (float *)pasub->vale;
	vfptr = (float *)pasub->valf;

	if((*dptr)==1)  {
	

}
*/

static long recordRefOrbit(aSubRecord *pasub)
{
	char  *aptr;
	float *bptr;

	float  *vaptr;


	aptr = (char *)pasub->a;
	bptr = (float *)pasub->b;

	vaptr = (float *)pasub->vala;
	if((*aptr)==1) {
	printf("record Ref Orb\n\r");
	memcpy(vaptr, bptr, 360*sizeof(float));
	}
	return 0;
}

static long recordRefOrbitXY(aSubRecord *pasub)
{
	char  *aptr;
	float *bptr;

	float  *vaptr;
	float  *vbptr;


	aptr = (char *)pasub->a;
	bptr = (float *)pasub->b;

	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;

	float temp[180];


	if((*aptr)==1) {
	printf("record Ref XY Orb\n\r");
	memcpy(temp, bptr, 180*sizeof(float));
	memcpy(vaptr, temp, 180*sizeof(float));

	//Shift
	memcpy(vbptr, (temp+174), 6*sizeof(float));
	vbptr += 6;
	memcpy(vbptr, temp, 174*sizeof(float));
	}

	return 0;
}

static long corSP(aSubRecord *pasub)
{
	float  *aptr,*bptr,*cptr,*dptr,*eptr,*fptr;
	float  *gptr,*hptr,*iptr,*jptr,*kptr,*lptr;
	float  *mptr;
	long   *nptr;

	float  *vaptr,*vbptr,*vcptr,*vdptr,*veptr,*vfptr;
	float  *vgptr,*vhptr,*viptr,*vjptr,*vkptr,*vlptr;

	float temp;

	aptr = (float *)pasub->a;
	bptr = (float *)pasub->b;
	cptr = (float *)pasub->c;
	dptr = (float *)pasub->d;
	eptr = (float *)pasub->e;
	fptr = (float *)pasub->f;
	gptr = (float *)pasub->g;
	hptr = (float *)pasub->h;
	iptr = (float *)pasub->i;
	jptr = (float *)pasub->j;
	kptr = (float *)pasub->k;
	lptr = (float *)pasub->l;

	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;
	vcptr = (float *)pasub->valc;
	vdptr = (float *)pasub->vald;
	veptr = (float *)pasub->vale;
	vfptr = (float *)pasub->valf;
	vgptr = (float *)pasub->valg;
	vhptr = (float *)pasub->valh;
	viptr = (float *)pasub->vali;
	vjptr = (float *)pasub->valj;
	vkptr = (float *)pasub->valk;
	vlptr = (float *)pasub->vall;

	mptr = (float *)pasub->m;
	nptr = (long *)pasub->n;

	int i;
	float deltaSP[360];
	memcpy(deltaSP,mptr,360*sizeof(float));

	for(i=0;i<360;i++) {
		if(deltaSP[i]>4.0) deltaSP[i]=4.0;
		if(deltaSP[i]<-4.0) deltaSP[i]=-4.0;
		//printf("i=%d deltaSP[i]=%f\n\r",i,deltaSP[i]);
		}

	int index= 0;
	index = ((long)(*nptr)-1)*6;

	temp = (float)(*aptr) + deltaSP[index];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vaptr = temp;

	temp = (float)(*bptr) + deltaSP[index+1];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vbptr = temp;

	temp = (float)(*cptr) + deltaSP[index+2];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vcptr = temp;

	temp = (float)(*dptr) + deltaSP[index+3];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vdptr = temp;

	temp = (float)(*eptr) + deltaSP[index+4];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*veptr = temp;

	temp = (float)(*fptr) + deltaSP[index+5];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vfptr = temp;

	temp = (float)(*gptr) + deltaSP[index+180];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vgptr = temp;

	temp = (float)(*hptr) + deltaSP[index+181];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vhptr = temp;

	temp = (float)(*iptr) + deltaSP[index+182];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*viptr = temp;

	temp = (float)(*jptr) + deltaSP[index+183];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vjptr = temp;

	temp = (float)(*kptr) + deltaSP[index+184];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vkptr = temp;

	temp = (float)(*lptr) + deltaSP[index+185];
	if(temp>17.999) temp=17.999;
	if(temp<-17.999) temp=-17.999;
	*vlptr = temp;

	/*
 	*vaptr = (float)(*aptr) + deltaSP[index];
 	*vbptr = (float)(*bptr) + deltaSP[index+1];
 	*vcptr = (float)(*cptr) + deltaSP[index+2];
 	*vdptr = (float)(*dptr) + deltaSP[index+3];
 	*veptr = (float)(*eptr) + deltaSP[index+4];
 	*vfptr = (float)(*fptr) + deltaSP[index+5];

 	*vgptr = (float)(*gptr) + deltaSP[index+181];
 	*vhptr = (float)(*hptr) + deltaSP[index+182];
 	*viptr = (float)(*iptr) + deltaSP[index+183];
 	*vjptr = (float)(*jptr) + deltaSP[index+184];
 	*vkptr = (float)(*kptr) + deltaSP[index+185];
 	*vlptr = (float)(*lptr) + deltaSP[index+186];
	*/

	return 0;
}

static long pidSP(aSubRecord *pasub)
{

	float  *aptr,*bptr,*cptr,*dptr,*eptr,*gptr,*hptr,*iptr, *lptr, *mptr,*nptr;
	char *fptr, *jptr, *kptr;
	float  *vaptr, *vbptr, *vcptr, *vdptr, *veptr, *vfptr,*vgptr,*vhptr;

	aptr = (float *)pasub->a;
	bptr = (float *)pasub->b;
	cptr = (float *)pasub->c;
	dptr = (float *)pasub->d;
	eptr = (float *)pasub->e;
	fptr = (char *)pasub->f;
	gptr = (float *)pasub->g;
	hptr = (float *)pasub->h;
	iptr = (float *)pasub->i;
	jptr = (char *)pasub->j;
	kptr = (char *)pasub->k;
	lptr = (float *)pasub->l;
	mptr = (float *)pasub->m;
	nptr = (float *)pasub->n;

	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;
	vcptr = (float *)pasub->valc;
	vdptr = (float *)pasub->vald;
	veptr = (float *)pasub->vale;
	vfptr = (float *)pasub->valf;
	vgptr = (float *)pasub->valg;
	vhptr = (float *)pasub->valh;

	int rowLength = 361;

	float SPSum[360];

	static float deltaSP[360];
	static float deltaSPReg[360];
	float deltaSPDiff[360];
	static float deltaSPSum[360];
	int i,j;
	
	float sp[360];
	float orb[360];
	float orbRef[360];
	float rvRow[360];	
	float deltaOrb[360];

	memcpy(orb, bptr, 180*sizeof(float));
	memcpy((orb+180), cptr, 180*sizeof(float));

	memcpy(orbRef, dptr, 180*sizeof(float));
	memcpy((orbRef+180), eptr, 180*sizeof(float));

	memcpy(SPSum, mptr, 360*sizeof(float));


	if(*kptr==0) {
		for(i=0;i<360;i++) {		
			//deltaSP			
			deltaSP[i]=0.0;
			memcpy(rvRow, (aptr+(i*rowLength)), rowLength*sizeof(float));
			//Add to (rowLength-1): disable the last data. Target sum is zero. So, zero*number = zeor.
			for(j=0;j< (rowLength-1);j++) {
				//remove "zero" position -- disabled BPM
				if(orb[j]==0) {
					printf("j=%d bad BPM data\n\r",j);
					deltaSP[i] += 0; }
				else 
				deltaSP[i] += (orbRef[j]-orb[j])*rvRow[j];	
			}		
			
			//deltaSP[i] = deltaSP[i]/1000000.0;
			deltaSP[i] = deltaSP[i]/unitScale;

			//I:sum
			if(((*hptr)==0)||((*fptr)==1)) deltaSPSum[i]=0;
			else deltaSPSum[i] = (deltaSPSum[i]*(*nptr) + deltaSP[i]);
			
			//diff
			deltaSPDiff[i]=	(deltaSP[i]-deltaSPReg[i]);

			// All
			sp[i]= (*gptr)*deltaSP[i] + (*hptr)*deltaSPSum[i] + (*iptr)*deltaSPDiff[i];

			//For SR, step less than 4A.
			if(sp[i]<-4.0) sp[i]=-4.0;
			if(sp[i]>4.0)  sp[i]=4.0;

			deltaSPReg[i] = deltaSP[i];
	
			//if diable, delta=0
			if((*jptr)==0) sp[i]=0;
			
			SPSum[i] += sp[i];
		}
		memcpy(vaptr, sp, 360*sizeof(float));
		memcpy(vfptr, SPSum,360*sizeof(float)); 
		memcpy(vgptr, deltaSPSum,360*sizeof(float)); 
		memcpy(vhptr, deltaSPDiff,360*sizeof(float)); 
	}
	else { 
	for(i=0;i<360;i++) SPSum[i]=0;
	memcpy(vfptr, SPSum,360*sizeof(float)); 
	memcpy(vaptr, lptr,360*sizeof(float)); 
	memcpy(deltaSP, lptr,360*sizeof(float)); 
	}

	//upate deltaOrbs
	float xRMS1, yRMS1, xyRMS1;
	float xRMS, yRMS, xyRMS;
	xRMS=0; 
	yRMS=0;
	xyRMS=0;
	for(i=0;i<360;i++) {
		deltaOrb[i]=orb[i]-orbRef[i];
		if(i<180) xRMS += (deltaOrb[i]*deltaOrb[i]/180.0);
		else yRMS += (deltaOrb[i]*deltaOrb[i]/180.0);
		xyRMS += (deltaOrb[i]*deltaOrb[i]/360.0);			
	}
	xRMS1 = sqrt(xRMS);
	yRMS1 = sqrt(yRMS);
	xyRMS1 = sqrt(xyRMS);
//	printf("xRMS=%f yRMS=%f xyRMS=%f\n\r", xRMS1, yRMS1, xyRMS1);
	*vcptr = xRMS1;
 	*vdptr = yRMS1;
	*veptr = xyRMS1;
	memcpy(vbptr, deltaOrb, 360*sizeof(float));

	return 0;
}

static long ORMConstruct(aSubRecord *pasub)
{
	float  *aptr,*cptr,*dptr,*eptr, *fptr;
	long   *bptr;

	aptr = (float *)pasub->a;
	bptr = (char *)pasub->b;
	cptr = (float *)pasub->c;
	dptr = (float *)pasub->d;
	eptr = (float *)pasub->e;
	fptr = (float *)pasub->f;

	long index;
	index=(long)(*bptr)-1;  //for easy to see R
	printf("\n\r\n\r  New colum constrution  ----> Index=%d  Kick=%f\n\r", index, (*aptr));

	float *vaptr,*vbptr,*vcptr,*vdptr,*veptr,*vfptr,*vgptr;
	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;
	vcptr = (float *)pasub->valc;
	vdptr = (float *)pasub->vald;
	veptr = (float *)pasub->vale;
	vfptr = (float *)pasub->valf;
	vgptr = (float *)pasub->valg;

	float tempR[129600];
	float *f1, *f2;

	float temp0[360], temp[360];
	int i;
	float kick;
	float *elementPtr;
	float *elementPtr1;
		
	int offsetR;

	float minR=100;
	float maxR=0;

	kick=(float)(*aptr);
	memcpy(temp0, cptr, 360*sizeof(float));
	memcpy(temp, dptr, 360*sizeof(float));
	
	int indexShift;
	int tempInt;

	if(index==0) {
		for(i=0;i<129600;i++) tempR[i]=0;
		memcpy(vaptr, tempR, 129600*sizeof(float));
	}
	tempInt = (int)(floor(index/6));
	
	printf("tempInt=%d\n\r",tempInt);

	if((tempInt % 2)==0)  {
		indexShift = (int)(floor(index/6)*3) + (int)(index%6);
		printf("indexShift/X=%d\n\r\n\r", indexShift);
	}
	else {
		indexShift = (int)(floor((index-6)/6)*3) + (int)(index%6)+180;
		printf("indexShift(180/Y)=%d\n\r\n", indexShift);
	}


	//normalize
	for(i=0;i<360;i++) {
		//temp[i]= (temp[i]-temp0[i])/(kick*1000000);  	// Use the unit of urad and um
		temp[i]= (temp[i]-temp0[i])/(kick*unitScale);

		if(minR > (abs(temp[i]))) minR=abs(temp[i]);
		if(maxR < (abs(temp[i]))) maxR=abs(temp[i]);

		offsetR = 360*i + indexShift;			
		elementPtr = vaptr + offsetR;
		*elementPtr = temp[i];
		if((i==0)||(i==359)) printf("two ends of one colum: i=%d offsetR=%d R[offset]=%f\n\r", i, offsetR, temp[i]);
		elementPtr1 = vbptr + i;
		*elementPtr1 = temp[i];
	}

	printf("col=%d   minR=%f   maxR=%f\n\r", index, minR, maxR);

	//move R to R1, R1 to R2. K to K1 and K1 to K2
	if(index==359) {
	//R1--> R2
	memcpy(veptr, eptr, 129600*sizeof(float));
	*vfptr = *fptr;
	memcpy(vcptr, vaptr, 129600*sizeof(float));
	*vdptr = *aptr;
	for(i=0;i<129600;i++) {
	f1 = vcptr + i;
	f2 = veptr + i;
	tempR[i]= (float)(*f2)-(float)(*f1);
	}
	memcpy(vgptr, tempR, 129600*sizeof(float));
	printf("-----------------------Moved--------------------\n\r");
	}
	
	return 0;
}

static long invalidMerge(aSubRecord *pasub)
{

	char  *aptr,*bptr,*cptr,*dptr,*eptr,*fptr;
	aptr = (char *)pasub->a;
	bptr = (char *)pasub->b;
	cptr = (char *)pasub->c;
	dptr = (char *)pasub->d;
	eptr = (char *)pasub->e;
	fptr = (char *)pasub->f;
	char invalid[6];
	invalid[0]= (char)(*aptr);
	invalid[1]= (char)(*bptr);
	invalid[2]= (char)(*cptr);
	invalid[3]= (char)(*dptr);
	invalid[4]= (char)(*eptr);
	invalid[5]= (char)(*fptr);
	memcpy(pasub->vala, invalid, 6*sizeof(char));
	
	return 0;
}	

static long invalidMerge1(aSubRecord *pasub)
{

	char  *inputPtr[15];
	char   *vaptr;

	inputPtr[0] = pasub->a;
	inputPtr[1] = pasub->b;
	inputPtr[2] = pasub->c;
	inputPtr[3] = pasub->d;
	inputPtr[4] = pasub->e;
	inputPtr[5] = pasub->f;
	inputPtr[6] = pasub->g;
	inputPtr[7] = pasub->h;
	inputPtr[8] = pasub->i;
	inputPtr[9] = pasub->j;
	inputPtr[10] = pasub->k;
	inputPtr[11] = pasub->l;
	inputPtr[12] = pasub->m;
	inputPtr[13] = pasub->n;
	inputPtr[14] = pasub->o;
	vaptr = (char *)pasub->vala;
	int i;
	for (i=0; i<15; i++) {
		memcpy(vaptr, inputPtr[i],6*sizeof(char));
		vaptr += 6;  
	}
	return 0;	
}

static long invalidMerge2(aSubRecord *pasub)
{

	char  *inputPtr[2];
	char   *vaptr;

	inputPtr[0] = pasub->a;
	inputPtr[1] = pasub->b;
	vaptr = (char *)pasub->vala;
	int i;
	for (i=0; i<2; i++) {
		memcpy(vaptr, inputPtr[i],90*sizeof(char));
		vaptr += 90;  
	}
	return 0;	
}

static long bpmMerge3(aSubRecord *pasub)
{

	float  *inputPtr[2];
	float   *vaptr;
	
	inputPtr[0] = pasub->a;
	inputPtr[1] = pasub->b;
	vaptr = (float *)pasub->vala;
	int i;
	for (i=0; i<2; i++) {
		memcpy(vaptr, inputPtr[i],180*sizeof(float));
		vaptr += 180;  
	}
	return 0;	
}

static long bpmMerge2(aSubRecord *pasub)
{

	float  *inputPtr[2];
	float   *vaptr;

	float   *vbptr;

	inputPtr[0] = pasub->a;
	inputPtr[1] = pasub->b;
	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;
	int i;
	for (i=0; i<2; i++) {
		memcpy(vaptr, inputPtr[i],90*sizeof(float));
		vaptr += 90;  
	}

//April 25: to shift the orbit following Lattice design: C30:1-6 is the first
//Last 6 values from C30:
	memcpy(vbptr, (inputPtr[1]+84),6*sizeof(float));
	vbptr += 6;  
//Then first segment of 15 Cells (90 values)
	memcpy(vbptr, inputPtr[0],90*sizeof(float));
	vbptr += 90;  
//Last step: the remaining 84 values of the 2nd segment
	memcpy(vbptr, inputPtr[1],84*sizeof(float));

	return 0;	
}

static long bpmMerge1(aSubRecord *pasub)
{

	float  *inputPtr[15];
	float   *vaptr;

	inputPtr[0] = pasub->a;
	inputPtr[1] = pasub->b;
	inputPtr[2] = pasub->c;
	inputPtr[3] = pasub->d;
	inputPtr[4] = pasub->e;
	inputPtr[5] = pasub->f;
	inputPtr[6] = pasub->g;
	inputPtr[7] = pasub->h;
	inputPtr[8] = pasub->i;
	inputPtr[9] = pasub->j;
	inputPtr[10] = pasub->k;
	inputPtr[11] = pasub->l;
	inputPtr[12] = pasub->m;
	inputPtr[13] = pasub->n;
	inputPtr[14] = pasub->o;
	vaptr = (float *)pasub->vala;
	int i;
	for (i=0; i<15; i++) {
		memcpy(vaptr, inputPtr[i],6*sizeof(float));
		vaptr += 6;  
	}
	return 0;	
}

static long bpmAverage(aSubRecord *pasub)
{

	float  *aptr,*bptr,*cptr,*dptr,*eptr,*fptr,*gptr,*hptr;
	char *iptr,*kptr,*lptr,*mptr,*nptr,*optr,*pptr;
	float *jptr;
	aptr = (float *)pasub->a;
	bptr = (float *)pasub->b;
	cptr = (float *)pasub->c;
	dptr = (float *)pasub->d;
	eptr = (float *)pasub->e;
	fptr = (float *)pasub->f;
	gptr = (float *)pasub->g;
	hptr = (float *)pasub->h;
	iptr = (char *)pasub->i;
	kptr = (char *)pasub->k;
	lptr = (char *)pasub->l;
	mptr = (char *)pasub->m;
	nptr = (char *)pasub->n;
	optr = (char *)pasub->o;
	pptr = (char *)pasub->p;
	jptr = (float *)pasub->j;

	float  *vaptr,*vbptr,*vcptr,*vdptr,*veptr,*vfptr;
	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;
	vcptr = (float *)pasub->valc;
	vdptr = (float *)pasub->vald;
	veptr = (float *)pasub->vale;
	vfptr = (float *)pasub->valf;

	float xSA[6];
	float sofbSum[6];
	float ormSum[6];
	float xSOFB[6];
	float xORM[6];

	int cycles, nSOFB, nORM;
	int i;

	nSOFB = (int)((float)(*gptr));
	nORM = (int)((float)(*hptr));	
	cycles = (int)((float)(*jptr));

	if((*iptr)!=0) {
	for (i=0; i<6; i++) {
		xSA[i]=0;
		sofbSum[i] = 0;
		ormSum[i]=0; 
		xSOFB[i]=0;
		xORM[i]=0; }
	} else {

	//Times enable bit k --> p
	xSA[0]= (*aptr)*(*kptr);
	xSA[1]= (*bptr)*(*lptr);
	xSA[2]= (*cptr)*(*mptr);
	xSA[3]= (*dptr)*(*nptr);
	xSA[4]= (*eptr)*(*optr);
	xSA[5]= (*fptr)*(*pptr);
	memcpy(vaptr,xSA,6*sizeof(float));
	
	memcpy(sofbSum,vbptr,6*sizeof(float));
	memcpy(ormSum,vcptr,6*sizeof(float));

	for(i=0;i<6;i++) {
	sofbSum[i] += xSA[i];
	ormSum[i] += xSA[i];
	}
	memcpy(vbptr,sofbSum,6*sizeof(float));
	memcpy(vcptr,ormSum,6*sizeof(float));

	if( ((cycles+1)% nSOFB)==0) {  //end of softAverage		
		xSOFB[0]=sofbSum[0]/nSOFB;
		xSOFB[1]=sofbSum[1]/nSOFB;
		xSOFB[2]=sofbSum[2]/nSOFB;
		xSOFB[3]=sofbSum[3]/nSOFB;
		xSOFB[4]=sofbSum[4]/nSOFB;
		xSOFB[5]=sofbSum[5]/nSOFB;
		memcpy(vdptr,xSOFB,6*sizeof(float));

		for(i=0;i<6;i++) sofbSum[i] = 0;
		memcpy(vbptr,sofbSum,6*sizeof(float));
		if( ((cycles+1) % (nSOFB*nORM))==0) {  //end of ormAverage
			xORM[0]=ormSum[0]/(nSOFB*nORM);
			xORM[1]=ormSum[1]/(nSOFB*nORM);
			xORM[2]=ormSum[2]/(nSOFB*nORM);
			xORM[3]=ormSum[3]/(nSOFB*nORM);
			xORM[4]=ormSum[4]/(nSOFB*nORM);
			xORM[5]=ormSum[5]/(nSOFB*nORM);
			memcpy(veptr,xORM,6*sizeof(float));

			for(i=0;i<6;i++) ormSum[i] = 0;
			memcpy(vcptr,ormSum,6*sizeof(float));
			}  //end of orm
		} //end of sofb
	
	}  //end of non-reset
	return(0);
}

static long corSP18To1(aSubRecord *pasub)
{

	float  *aptr,*bptr,*cptr,*dptr,*eptr,*fptr;
	float  *gptr,*hptr,*iptr,*jptr,*kptr,*lptr;
	float  *mptr,*nptr,*optr,*pptr,*qptr,*rptr;
	float  *vaptr;
	float temp[18];
	int i;

	aptr = (float *)pasub->a;
	bptr = (float *)pasub->b;
	cptr = (float *)pasub->c;
	dptr = (float *)pasub->d;
	eptr = (float *)pasub->e;
	fptr = (float *)pasub->f;
	gptr = (float *)pasub->g;
	hptr = (float *)pasub->h;
	iptr = (float *)pasub->i;
	jptr = (float *)pasub->j;
	kptr = (float *)pasub->k;
	lptr = (float *)pasub->l;
	mptr = (float *)pasub->m;
	nptr = (float *)pasub->n;
	optr = (float *)pasub->o;
	pptr = (float *)pasub->p;
	qptr = (float *)pasub->q;
	rptr = (float *)pasub->r;
	vaptr = (float *)pasub->vala;
	temp[0]=*aptr;
	temp[1]=*bptr;
	temp[2]=*cptr;
	temp[3]=*dptr;
	temp[4]=*eptr;
	temp[5]=*fptr;
	temp[6]=*gptr;
	temp[7]=*hptr;
	temp[8]=*iptr;
	temp[9]=*jptr;
	temp[10]=*kptr;
	temp[11]=*lptr;
	temp[12]=*mptr;
	temp[13]=*nptr;
	temp[14]=*optr;
	temp[15]=*pptr;
	temp[16]=*qptr;
	temp[17]=*rptr;
	//for(i=0;i<18;i++) printf("i=%d, temp[i]=%f\n\r",i, temp[i]);
	memcpy(vaptr,temp,18*sizeof(float));
	return(0);
}

static long corSPMerge(aSubRecord *pasub)
{

	float  *inputPtr[20];
	float  *vaptr,*vbptr,*vcptr;
	inputPtr[0] = pasub->a;
	inputPtr[1] = pasub->b;
	inputPtr[2] = pasub->c;
	inputPtr[3] = pasub->d;
	inputPtr[4] = pasub->e;
	inputPtr[5] = pasub->f;
	inputPtr[6] = pasub->g;
	inputPtr[7] = pasub->h;
	inputPtr[8] = pasub->i;
	inputPtr[9] = pasub->j;
	inputPtr[10] = pasub->k;
	inputPtr[11] = pasub->l;
	inputPtr[12] = pasub->m;
	inputPtr[13] = pasub->n;
	inputPtr[14] = pasub->o;
	inputPtr[15] = pasub->p;
	inputPtr[16] = pasub->q;
	inputPtr[17] = pasub->r;
	inputPtr[18] = pasub->s;
	inputPtr[19] = pasub->t;

	vaptr = (float *)pasub->vala;
	vbptr = (float *)pasub->valb;
	vcptr = (float *)pasub->valc;

	int i;
	for (i=0; i<10; i++) {
		memcpy(vaptr, inputPtr[i],18*sizeof(float));
		vaptr += 18;  
		memcpy(vcptr, inputPtr[i],18*sizeof(float));
		vcptr += 18;  
	}
	for (i=10; i<20; i++) {
		memcpy(vbptr, inputPtr[i],18*sizeof(float));
		vbptr += 18;  
		memcpy(vcptr, inputPtr[i],18*sizeof(float));
		vcptr += 18;  
	}
//	memcpy(vcptr, pasub->vala, 180*sizeof(float));
//	vcptr += 180;  
//	memcpy(vcptr, pasub->valb, 180*sizeof(float));
	return(0);
}


epicsRegisterFunction(ORMConstruct);
epicsRegisterFunction(bpmAverage);
epicsRegisterFunction(bpmMerge1);
epicsRegisterFunction(bpmMerge2);
epicsRegisterFunction(bpmMerge3);
epicsRegisterFunction(invalidMerge);
epicsRegisterFunction(invalidMerge1);
epicsRegisterFunction(invalidMerge2);
epicsRegisterFunction(pidSP);
epicsRegisterFunction(corSP);
epicsRegisterFunction(recordRefOrbit);
epicsRegisterFunction(recordRefOrbitXY);
epicsRegisterFunction(corSP18To1);
epicsRegisterFunction(corSPMerge);


