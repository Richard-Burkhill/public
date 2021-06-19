#!/usr/bin/python3

import sys

JAN_DAYS = 31
FEB_DAYS = 28
MAR_DAYS = 31
APR_DAYS = 30
MAY_DAYS = 31
JUN_DAYS = 30
JUL_DAYS = 31
AUG_DAYS = 31
SEP_DAYS = 30
OCT_DAYS = 31
NOV_DAYS = 30
DEC_DAYS = 31

CUMULATIVE_FEB_DAYS = 31
CUMULATIVE_MAR_DAYS = 59
CUMULATIVE_APR_DAYS = 90
CUMULATIVE_MAY_DAYS = 120
CUMULATIVE_JUN_DAYS = 151
CUMULATIVE_JUL_DAYS = 181
CUMULATIVE_AUG_DAYS = 212
CUMULATIVE_SEP_DAYS = 243
CUMULATIVE_OCT_DAYS = 273
CUMULATIVE_NOV_DAYS = 304
CUMULATIVE_DEC_DAYS = 334

LEAP_YEAR_DAYS = 366
YEAR_DAYS = 365

monthStartDays = []

# Function to determine leap year status
def isLeapYear( year ):
    return ((year % 4) == 0) or ((( year % 100) == 0) and ((year % 400) == 0))

# 1st January was a Monday in the year 2018
# Going back from 2018 1999 started on a Friday
# Count the number of leap years preceeding 2000 and entered year
# Count the number of non-leap years preceeding 2000 and enetered year
# Take two days off per non-leap year
# Take a day off per non-leap year
def differenceDays (year1, year2):
    nonLeapYear = 0
    leapYear = 0
    while (year1 > year2):
        year1-=1
        if isLeapYear(year1):
            leapYear+=1
        else:
            nonLeapYear+=1
    return (leapYear*2)+nonLeapYear

def strDayToNumDay(strDay):
    day = 1
    if (startDay == "Monday"):
        day = 1
    elif (startDay == "Tuesday"):
        day = 2
    elif (startDay == "Wednesday"):
        day = 3
    elif (startDay == "Thursday"):
        day = 4
    elif (startDay == "Friday"):
        day = 5
    elif (startDay == "Saturday"):
        day = 6
    elif (startDay == "Sunday"):
        day = 7

    return day

def addDay (startDay, numDays):
    day = strDayToNumDay(startDay)
    day += numDays
    day %= 7
    returnDay = "Monday"

    if (day == 1):
        returnDay = "Monday"
    elif (day == 2):
        returnDay = "Tuesday"
    elif (day == 3):
        returnDay = "Wednesday"
    elif (day == 4):
        returnDay = "Thursday"
    elif (day == 5):
        returnDay = "Friday"
    elif (day == 6):
        returnDay = "Saturday"
    elif (day == 0):
        returnDay = "Sunday"

    return returnDay

# Function to determine start day of year
# Modulo 7 gives number of days back from Saturday
def startDayOfYear (year):
    days = 0
    if (year > 2018):
        days = differenceDays(year, 2018)
    else:
        days = differenceDays(2018, year)
    days=days%7
    return addDay("Monday", days)

# Function to determine start day of month in year
# Call start day of year
def startDay (monthName, year):
    startDayVar = startDayOfYear(year)
    leapYear = isLeapYear(year)
    if (monthName == "January"):
        return startDayVar
    elif(monthName == "February"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_FEB_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_FEB_DAYS)
    elif(monthName == "March"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_MAR_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_MAR_DAYS)
    elif(monthName == "April"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_APR_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_APR_DAYS)
    elif(monthName == "May"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_MAY_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_MAY_DAYS)
    elif(monthName == "June"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_JUN_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_JUN_DAYS)
    elif(monthName == "July"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_JUL_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_JUL_DAYS)
    elif(monthName == "August"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_AUG_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_AUG_DAYS)
    elif(monthName == "September"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_SEP_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_SEP_DAYS)
    elif(monthName == "October"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_OCT_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_OCT_DAYS)
    elif(monthName == "November"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_NOV_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_NOV_DAYS)
    elif(monthName == "December"):
        if (leapYear):
            return addDay(startDayVar, (CUMULATIVE_DEC_DAYS+1))
        else:
            return addDay(startDayVar, CUMULATIVE_DEC_DAYS)
    

# Function to determine part or whole weeks in month
def numDays (monthName, leapYear):
    numMonthDays = 0
    if (monthName == "January"):
        numMonthDays = JAN_DAYS
    elif(monthName == "February"):
        if (leapYear):
            numMonthDays = (FEB_DAYS+1)
        else:
            numMonthDays = FEB_DAYS
    elif(monthName == "March"):
        numMonthDays = MAR_DAYS
    elif(monthName == "April"):
        numMonthDays = APR_DAYS
    elif(monthName == "May"):
        numMonthDays = MAY_DAYS
    elif(monthName == "June"):
        numMonthDays = JUN_DAYS
    elif(monthName == "July"):
        numMonthDays = JUL_DAYS
    elif(monthName == "August"):
        numMonthDays = AUG_DAYS
    elif(monthName == "September"):
        numMonthDays = SEP_DAYS
    elif(monthName == "October"):
        numMonthDays = OCT_DAYS
    elif(monthName == "November"):
        numMonthDays = NOV_DAYS
    elif(monthName == "December"):
        numMonthDays = DEC_DAYS

    return (numMonthDays)

def numWeeks (monthName, leapYear):
    return (numDays(monthName, leapYear)//7)

def monthStartWeek (monthStartDay, cumulativeWeeks):
    returnValue=int(cumulativeWeeks)
    if (monthStartDay == "Monday"):
        returnValue+=1
    else:
        returnValue+=1
    return returnValue

def shortMonth(monthName):
    if (monthName == "January"):
        return "Jan"
    elif(monthName == "February"):
        return "Feb"
    elif(monthName == "March"):
        return "Mar"
    elif(monthName == "April"):
        return "Apr"
    elif(monthName == "May"):
        return "May"
    elif(monthName == "June"):
        return "Jun"
    elif(monthName == "July"):
        return "Jul"
    elif(monthName == "August"):
        return "Aug"
    elif(monthName == "September"):
        return "Sep"
    elif(monthName == "October"):
        return "Oct"
    elif(monthName == "November"):
        return "Nov"
    elif(monthName == "December"):
        return "Dec"

def htmlMonth (dhtmlDoc, monthName, year, startWeek):
    dhtmlDoc.write("<table border=\"5px\" bordercolor=\"#8707B0\">\n  <th style=\"text-align:center\">"+shortMonth(monthName)+"</th>\n")
    dhtmlDoc.write("<tr>\n    <td>Wk</td>\n    <td>M</td>\n    <td>T</td>\n    <td>W</td>\n    <td>T</td>\n    <td>F</td>\n    <td>S</td>\n    <td>S</td>\n</tr>\n")
    SundayDayConst=7
    weekNum=0
    monthStartDay=startDay (monthName, year)
    day=0
    if (monthStartDay == "Monday"):
        day = 1
    elif (monthStartDay == "Tuesday"):
        day = 2
    elif (monthStartDay == "Wednesday"):
        day = 3
    elif (monthStartDay == "Thursday"):
        day = 4
    elif (monthStartDay == "Friday"):
        day = 5
    elif (monthStartDay == "Saturday"):
        day = 6
    elif (monthStartDay == "Sunday"):
        day = 7

    print(shortMonth(monthName))
    #print(monthStartDay)
    print("day :"+str(day))

    leapYear = isLeapYear(year)
    days=numDays(monthName, leapYear)
    weeks=numWeeks(monthName, leapYear)
    print("days :"+str(days))
    #print("weeks :"+str(weeks))
    #print("firstDay :"+firstDay)

    weeksIndex=0
    dayCount=1
    endDay=7
    while(dayCount<=days):
        print("dayCount :"+str(dayCount))
        dhtmlDoc.write("<tr>\n    <td>"+str(startWeek)+"</td>\n")
        if (days-(weeksIndex*7)>=7):
            endDay=7
        else:
            endDay=(days-dayCount)+1
        print("endDay :"+str(endDay))
        weekCount=1
        for weekSlot in [1, 2, 3, 4, 5, 6, 7]:
            if ((weeksIndex*7)+weekSlot) >= day:
                if weekSlot <= endDay:
                    dhtmlDoc.write("    <td>"+str(dayCount)+"</td>\n")
                    dayCount+=1
                    weekCount+=1
                else:
                    if endDay == 7:
                        weeksIndex+=1
                    return weeksIndex
            else:
                dhtmlDoc.write("    <td></td>\n")
            #print("day :"+str(day))
        day=1
        dhtmlDoc.write("</tr>\n")
        weeksIndex+=1
        startWeek+=1
    return 0

def htmlTemplate(dhtmlDoc):
    dhtmlDoc.write("\n<!doctype html>\n\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n")
    dhtmlDoc.write("<title>The HTML5 Herald</title>\n<meta name=\"description\" content=\"The HTML5 Herald\">\n")
    dhtmlDoc.write("<meta name=\"author\" content=\"SitePoint\">\n<link rel=\"stylesheet\" href=\"css/styles.css?v=1.0\">\n")
    dhtmlDoc.write("</head>\n\n<body>\n<script src=\"js/scripts.js\"></script>\n")


def generateYear (year):
    dhtmlDoc = open("Calendar.html", "w")
    htmlTemplate(dhtmlDoc)
    janStartWeek = 1

    totalWeeks = htmlMonth(dhtmlDoc, "January", year, janStartWeek)
    totalWeeks += htmlMonth(dhtmlDoc, "February", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "March", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "April", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "May", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "June", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "July", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "August", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "September", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "October", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "November", year, totalWeeks)
    totalWeeks += htmlMonth(dhtmlDoc, "December", year, totalWeeks)

    dhtmlDoc.close()

def main (year):
    generateYear(year)

if __name__ == "__main__":
    args = sys.argv[1:]
    main(int(args[0]))
