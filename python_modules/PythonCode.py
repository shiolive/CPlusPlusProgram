import re
import string

def FindFrequency(item):
    file = open("Groceries", "r")
    count = 0
    item = item.lower() #convert user input item to lower case to ensure accuracy in comparison
    for word in file: #iterate through Grocery file
        word = word.strip()  #remove any additional white space
        word = word.lower()  #convert word in file to lower case for comparison
        if word == item:
            count += 1
    file.close()
    return count  #return value frequency


def PrintItems():
    file = open("Groceries", "r")
    for item in file: #iterate through file to print each item
        item = item.strip() #remove extra white space to ensure clean output
        print(item, FindFrequency(item), "\n") #use established function for simplicity in code
    file.close()


def FileData():
    file = open("Groceries", "r")
    data = open("frequency.dat", "w") #create file or overwrite file

    for item in file: #iterate through file
        item = item.strip() #remove extra whitespace for clean output
        count = FindFrequency(item) #find frequency of each item
        data.write(item + " " + str(count) + "\n") #write to file item and frequency

    file.close()
    data.close()






