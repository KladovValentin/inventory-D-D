import sys
import pygsheets

#authorizing in google API, to get access to google sheets
gc = pygsheets.authorize(client_secret='client_secret.json')
sh = gc.open_by_url('https://docs.google.com/spreadsheets/d/1We1l0yebch7SpZkEVD77KmwEhwb1H-GPil-ObSyjiTA')
wk1 = sh.sheet1

# writing
print("wait a bit")
file1 = open("./itemsOUT.txt","r")
for x in range(5):
    print(str(x)+" item")
    file1.readline()
    itemName = file1.readline()
    itemType = file1.readline()
    itemDescription = file1.readline()
    templine = file1.readline()
    itemMass = templine.split(' ')[0]
    itemValue = templine.split(' ')[1]
    itemAmount = templine.split(' ')[2]

    wk1.update_value('H'+str(x+97), itemName)
    if itemDescription != "\n":
        wk1.cell((97+x,8)).note = itemDescription
    wk1.update_value('I'+str(x+97), itemMass)
    wk1.update_value('J'+str(x+97), itemValue)
    wk1.update_value('K'+str(x+97), itemAmount)
file1.close()
print("values are writen")

    

