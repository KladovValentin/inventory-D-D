from re import M
import sys
import os
os.system('pip install pygsheets')
import pygsheets
#os.system('pip install googletrans')
#from googletrans import Translator

#translator = Translator()

#authorizing in google API, to get access to google sheets
gc = pygsheets.authorize(client_secret='client_secret.json')
sh = gc.open_by_url('https://docs.google.com/spreadsheets/d/1We1l0yebch7SpZkEVD77KmwEhwb1H-GPil-ObSyjiTA')
wk1 = sh.sheet1


# reading
print("wait a bit")
file1 = open("./items.txt","w")
for x in range(5):
    if (x+117+1 != 129) and (x+117+1 !=165) and (x+117+1 !=182) and (x+117+1 != 239):
        print(str(x+117)+" item")
        itemName = wk1.cell((117+x,1)).value
        if (itemName != None):
            #print(translator.translate(str(itemName), dest='en').text)
            itemType = 'quest items'
            if x+117+1>115:
                itemType = 'quest items'
            if x+117+1>128:
                itemType = 'equipment'
            if x+117+1>164:
                itemType = 'usefull gear'
            if x+117+1>181:
                itemType = 'spendable'
            if x+117+1>238:
                itemType = 'random stuff'
            
            itemDescriptionl = wk1.cell((117+x,1)).note
            itemDescription = None
            if itemDescriptionl != None:
                itemDescription = itemDescriptionl.replace('\n',' ')
            
            itemMass = str(wk1.cell((117+x,2)).value)
            if (itemMass == ''):
                itemMass = '0'
            
            itemValue = wk1.cell((117+x,3)).value
            if (itemValue == ''):
                itemValue = '0'
            
            itemAmount = wk1.cell((117+x,4)).value
            if (itemAmount == ''):
                itemAmount = '1'

            file1.write("\n")
            file1.write(itemName + "\n")
            file1.write(itemType + "\n")
            if itemDescription != None:
                file1.write(itemDescription + "\n")
            else:
                file1.write("\n")
            file1.write(itemMass + " " + itemValue + " " + itemAmount  + "\n")

file1.close()
print("values are extracted")
