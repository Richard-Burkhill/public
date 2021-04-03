#import the pandas library and aliasing as pd
import math
import pandas as pd
import numpy

def calcMean( dl ):
	total = sum(dl)
	n = len(dl)
	return (total / n)

def portfolioMean(returns, proportions):
	if (len(returns)==len(proportions)):
		count=0
		proportionOfReturn=[]
		for proportion in proportions:
			proportionOfReturn[count]=(returns[count]*proportion)
		
	return sum(proportionOfReturn)

#Should give the same answer as portfolioMean, however harmonicMeans can only be calculated for portfolios of equal proportions
def harmonicMean(dl):
	n=len(dl)
	dlInverse=[]
	count=0
	for item in dl:
		dlInverse[count]=(1/item)
		count+=1
	return (n/sum(dlInverse))

#normally used to calculate average compound growth rate
def geometricMean(percentagesPerCompoundPeriod):
	multipliers=[]
	count=0
	for percentage in percentagesPerCompoundPeriod:
		multipliers[count]=1+(percentage/100)
		count+=1
	prodMultipliers=numpy.prod(multipliers)
	return pow(prodMultipliers, (1/count))

#Python3 can return a float as a result of diving 2 integers, Python2 only returns an ineteger
def calcMedian ( dl ):
	n= len(dl)
	posOfMedian = ((n+1)/2)
	posOfMedianFloor = ((n+1)//2)-1
	if (math.remainder(posOfMedian, 1) > 0.0):
		return ((dl[posOfMedianFloor] + dl[(posOfMedianFloor+1)]) / 2)
	else:
		return dl[posOfMedian]

def modesIfAny(dl):
	listOfModalGroups = []
	if (len(dl) > 0):
		dl.sort()
		prev = dl[0]
		curMostFreq = 0
		freq = 1
		modalGroup = 0
		prev= dl[0]
		for i in range (1, len(dl)):
			if (prev == dl[i]):
				freq+=1
				if (freq > curMostFreq):
					curMostFreq = [freq][0]
			else:
				freq=1
			prev = dl[i]

		#Check for their being the same number of each item
		count = 1
		prev = dl[0]
		for i in range (1, len(dl)):
			if (prev == dl[i]):
				count+=1
			else:
				if (count == curMostFreq):
					listOfModalGroups.append(dl[i-1])
				else:
					modalGroup = 1
				count=1
			prev = dl[i]
			
		if (count == curMostFreq):
			listOfModalGroups.append(dl[(len(dl)-1)])
		else:
			modalGroup = 1
		if (modalGroup == 0):
			listOfModalGroups.clear()
				
	return listOfModalGroups

def locationOfPercentile(dl, fraction):
	sort(dl)
	n=len(dl)
	return ((n+1)*fraction)

def valueOfPercentile(dl, fraction):
	return dl[locationOfPercentile(dl, fraction)]

def columnNames( df ):
	return df.columns.values

def isNumber( df ):
	return ((df.dtypes == 'float64') or (df.dtypes == 'int64'))

#Measure how spread out a set of data is
def measureOfDispersion(dl):
	mean=calcMean(dl)
	differencesFromMean = []
	count=0
	for di in dl:
		differencesFromMean[count]=(di-mean)
		count+=1
	return (sum(differencesFromMean)/count)

#Calculates the variance of each column in the data frame
def variance( df ):
	for column in df:
		if isNumber( column ):
			itemCount = 0
			mean = calcMean( column )
			deviations = column
			for item in column:
				deviations[itemCount] = (column[itemCount] - mean)
				itemCount+=1
		sumDeviation = 0.0
		for deviation in deviations:
			sumDeviation += deviation
		return (sumDeviation / itemCount)
	return float('nan')

def calcSD ( variance ):
	return math.sqrt ( variance )

#Move a piece of data onto the standard normal distribution, by providing the data value,
#the standard deviation and the mean of the normal distribution in which the data item sits
def z_score ( x, mean, sd ):
	return (x - mean) / sd

#Positive skewness indicates a greater likely hood of winning big,
#with an increased liklihood of loosing small
def calcSkewness(dl):
	mean=calcMean(dl)
	sd=calcSD(dl)
	sdCubed=pow(sd,3)
	deviationCubed = []
	itemCount=0
	for di in dl:
		deviationCubed[itemCount]=pow(di-mean,3)
		itemCount+=1
	return (sum(deviationCubed)/sdCubed)

#A large kurtosis figure indicates that there is an unusual proportion of data in the top and bottom ranges
def calcKurtosis(dl):
	mean=calcMean(dl)
	sd=calcSD(dl)
	sdQuad=pow(sd,4)
	deviationQuad = []
	itemCount=0
	for di in dl:
		deviationQuad[itemCount]=pow(di-mean,4)
		itemCount+=1
	return (sum(deviationQuad)/sdQuad)

def calcCoefficientOfVariation(dl):
	sd=calcSD(dl)
	mean=calcMean(dl)
	return (sd/mean)

#Calculated by Chebyshev's Inequality formula
def probMinDataItemsInNumOfSDs(numberOfSDs):
	return (1-(1/pow(numberOfSDs,2)))

def futureValue(presentValue, ratePerCompoundPeriod, compoundPeriods):
	return presentValue*pow((1+(ratePerCompoundPeriod/100), compoundPeriods)

def futureValueAPR(presentValue, APR, years, compoundsPerYear):
	return presentValue*pow(((1+((APR/100)compoundsPerYear)/, (compoundPeriods*compoundsPerYear)))

def effectiveAnnualInterestRate(ratePerCompoundPeriod, compoundsPerYear):
	return (pow(1+(ratePerCompoundPeriod/100)), compoundsPerYear)-1)

def futureValueContCompounding(presentValue, ratePerCompoundPeriod, compoundPeriods):
	rate=ratePerCompoundPeriod/100
	math.log(rate*compoundPeriods)
	return presentValue*math.log(rate*compoundPeriods)

def presentValueOfPerpetuity(perpetualPayment, interestRate):
	return (perpetualPayment/(interestRate/100))

def futureValueOfOridinaryAnnuity(presentValue, years, rate):
	multiplier=1+(rate/100)
	for year in range (1, years)
		multiplier*=pow(multiplier, year)
	return (presentValue*multiplier)

