import os

def check_int(s):
    if s[0] in ('-', '+'):
        return s[1:].isdigit()
    return s.isdigit()

def main():

	print("Bienvenido al sistema de creación de Inmuneratio.")
	print("Este programa permitirá crear la estructura inicial para iniciar un nuevo proyecto con el framework. Para ello, debe responder a la siguientes preguntas sobre el proyecto\n")

	nombreP = input("Nombre del proyecto: ")

	while(True):
		ch1 = input("¿Desea crear la estructura inicial por defecto?(y/n): ")
		if ch1 == "y" or len(ch1) == 0:
			break
		elif ch1 == "n":
			break
		else:
			print("Ingrese un valor valido.")

	if ch1 == "y" or len(ch1) == 0:
		nCel = 1
		namesCell = ["Celula"]
		ch5 = "1"
		resDng = [True,True,True,True,True,True,True,True,True]
		ch7U = [23, 22, 21, 139, 512, 111, 2049, 4045, 135, 137, 138, 139, 445, 6000, 6255, 53, 389, 25, 109, 143, 80, 443, 8000, 20, 37, 69, 79, 119, 123, 515, 514, 161, 162, 179, 1080]
		ch7T = [23, 22, 21, 139, 512, 111, 2049, 4045, 135, 137, 138, 139, 445, 6000, 6255, 53, 389, 25, 109, 143, 80, 443, 8000, 20, 37, 69, 79, 119, 123, 515, 514, 161, 162, 179, 1080]



	else:

		while(True):
			ch2 = input("Número de tipos de células: ")
			if len(ch2) == 0:
				nCel = 1
				break
			elif not (check_int(ch2)):
				print("El valor no es un número. Ingrese el valor nuevamente.")
			else:
				nCel = int(ch2)
				break

		namesCell = []

		for i in range(nCel):

			ch3 = input("Nombre de la célula "+str(i+1)+": ")
			if len(ch3) == 0:
				namesCell.append("Celula1")
			else:
				namesCell.append(ch3)

		while(True):
			ch5 = input("\nMódulos de obtención de antigeno a utilizar (1: Sniffer y Peligro, 2: Sniffer, 3: Peligro): ")
			if len(ch5) == 0:
				ch5 = "1"
				break
			elif ch5 in "123":
				break
			else:
				print("Ingrese un valor valido.")

		if ch5 in "13":
			while(True):
				ch6 = input("\n¿Desea definir las caracteristicas de los antigenos producidos por el módulo de Peligro? (y/n): ")
				if ch6 == "y" or len(ch6) == 0:
					break
				elif ch6 == "n":
					break
				else:
					print("Ingrese un valor valido.")

			if ch6 == "y":
				var = ["Uso de disco", "Uso de CPU", "Uso de memoria RAM", "Bytes recibidos en red", "Bytes enviados en red", "Número de conexiones", "Número de procesos", "Número de logs", "Número de logs fallidos"]
				resDng = []

				for v in var:
					while(True):
						ch7 = input(v + " (y/n): ")
						if ch7 == "y" or len(ch7) == 0:
							resDng.append(True)
							break
						elif ch7 == "n":
							resDng.append(False)
							break
						else:
							print("Ingrese un valor valido.")
			else:
				resDng = [True,True,True,True,True,True,True,True,True]

		if ch5 in "12":
			while(True):
				ch6 = input("\n¿Desea definir las caracteristicas de los antigenos producidos por el módulo Sniffer? (y/n): ")
				if ch6 == "y" or len(ch6) == 0:
					break
				elif ch6 == "n":
					break
				else:
					print("Ingrese un valor valido.")

			if ch6 == "y":

				ch7T = input("Ingrese los puertos que serán capturados con protocolo TCP: ")

				ch7T = [int(x) for x in ch7T.split()]

				ch7U = input("Ingrese los puertos que serán capturados con protocolo UDP: ")

				ch7U = [int(x) for x in ch7U.split()]

			else:
				ch7U = [23, 22, 21, 139, 512, 111, 2049, 4045, 135, 137, 138, 139, 445, 6000, 6255, 53, 389, 25, 109, 143, 80, 443, 8000, 20, 37, 69, 79, 119, 123, 515, 514, 161, 162, 179, 1080]
				ch7T = [23, 22, 21, 139, 512, 111, 2049, 4045, 135, 137, 138, 139, 445, 6000, 6255, 53, 389, 25, 109, 143, 80, 443, 8000, 20, 37, 69, 79, 119, 123, 515, 514, 161, 162, 179, 1080]


	#try:
	os.mkdir(nombreP)

	##################################

	with open("base_files/ADTAdministrator.cpp", "r") as f:
		text = f.read()

	a = ""

	if ch5 in "12":
		a = a + '''sniffer.stopSniffer();
thSniffer->join();
delete thSniffer;\n'''

	if ch5 in "13":
		a = a + '''	danger.stopDanger();
thDanger->join();
delete thDanger;'''

	b = namesCell[0]

	c = ""
	if ch5 in "12":
		c = c + "\tthSniffer = new thread(&Sniffer::snifferRun, &sniffer);\n"

	if ch5 in "13":
		c = c + "\tthDanger = new thread(&Danger::dangerRun, &danger);"

	text = text.format(a,b,c)

	with open(nombreP + "/" + "ADTAdministrator.cpp", "w") as f:
		f.write(text)

	######################################

	with open("base_files/ADTCell.cpp", "r") as f:
		text = f.read()

	for i in range(nCel):
		a = namesCell[i]
		t = text.format(a)

		with open(nombreP + "/" + "ADT"+namesCell[i]+".cpp", "w") as f:
			f.write(t)

	######################################

	with open("base_files/ADTPopulation.cpp", "r") as f:
		text = f.read()

	for i in range(nCel):
		b = namesCell[i]
		a = "Population_" + namesCell[i]
		t = text.format(a, b)

		with open(nombreP + "/" + "ADT"+a+".cpp", "w") as f:
			f.write(t)

	######################################

	with open("base_files/Administrator.cpp", "r") as f:
		text = f.read()

	a = ""
	b1 = ""
	b2 = ""

	if ch5 in "12":
		b1 = b1 + "vector<Antigen> antigen = sniffer.getSnifferAntigens();\n\t\t"

	if ch5 in "13":
		b2 = b2 + "vector<Antigen> antigen2 = danger.getDangerAntigens();\n\t\t"

	for i in range(nCel):
		t = "population"+str(i+1)+" = "+"Population_" + namesCell[i]+"<"+namesCell[i]+", Administrator>(100, this);\n"
		a = a + t

		if ch5 in "12":
			b1 = b1 + "population"+str(i+1)+".go(antigen);\n\t\t"

		if ch5 in "13":
			b2 = b2 + "population"+str(i+1)+".go(antigen2);\n\t\t"		

	text = text.format(a, b1, b2)

	with open(nombreP + "/" + "Administrator.cpp", "w") as f:
		f.write(text)

	##################################

	with open("base_files/Administrator.h", "r") as f:
		text = f.read()

	a = ""
	b = ""
	c = ""
	d = ""

	for i in range(nCel):
		t = '#include "{0}.h"\n'
		a = a + t.format("Population_" + namesCell[i])
		a = a + t.format(namesCell[i])

		t = '{0}<{1}, Administrator> population{2};\n'
		b = b + t.format("Population_" + namesCell[i], namesCell[i], str(i+1))

	t = '#include "{0}.h"\n'

	if ch5 in "12":
		d = d + "Sniffer sniffer;\n\tthread *thSniffer;\n\n\t"
		a = a + t.format("Sniffer")
	if ch5 in "13":
		d = d + "Danger danger;\n\tthread *thDanger;"
		a = a + t.format("Danger")

	text = text.format(a,b,namesCell[0],d)

	with open(nombreP + "/" + "Administrator.h", "w") as f:
		f.write(text)

	######################################

	with open("base_files/Cell.cpp", "r") as f:
		text = f.read()

	for i in range(nCel):
		a = namesCell[i]
		t = text.format(a)

		with open(nombreP + "/" +a+".cpp", "w") as f:
			f.write(t)

	######################################

	with open("base_files/Cell.h", "r") as f:
		text = f.read()

	for i in range(nCel):
		a = namesCell[i]
		t = text.format(a)

		with open(nombreP + "/" +a+".h", "w") as f:
			f.write(t)

	######################################

	if ch5 in "13":

		with open("base_files/Danger.cpp", "r") as f:
			text = f.read()

		a = "{"
		for i in range(9):
			if resDng: a = a+"true"
			else: a = a+"false"

			if i != 8: a = a+","
		a = a + "}"

		text = text.format(a)

		with open(nombreP + "/" + "Danger.cpp", "w") as f:
			f.write(text)

	######################################

	with open("base_files/Population.cpp", "r") as f:
		text = f.read()

	for i in range(nCel):
		a = namesCell[i]
		t = text.format("Population_" + namesCell[i], a)

		with open(nombreP + "/" +"Population_" + namesCell[i]+".cpp", "w") as f:
			f.write(t)

	######################################

	with open("base_files/Population.h", "r") as f:
		text = f.read()

	for i in range(nCel):
		a = namesCell[i]
		t = text.format("Population_" + namesCell[i], a)

		with open(nombreP + "/" +"Population_" + namesCell[i]+".h", "w") as f:
			f.write(t)

	###############################

	if ch5 in "12":

		with open("base_files/Sniffer.cpp", "r") as f:
			text = f.read()

		t = '''if (sp == {0} || dp == {0}){{ vecBool.push_back(true);}}
	    else{{vecBool.push_back(false);}}\n\n'''

		a = ""
		for i in range(len(ch7T)):
			a = a + t.format(ch7T[i])

		text = text.format(a)

		with open(nombreP + "/" + "Sniffer.cpp", "w") as f:
			f.write(text)

	##################################

	with open("base_files/main.cpp", "r") as f:
		text = f.read()

	a = ""
	t = '#include "{0}.h"\n'

	for i in range(nCel):

		a = a + t.format("Population_" + namesCell[i])
		a = a + t.format(namesCell[i])

	text = text.format(a)

	with open(nombreP + "/" + "main.cpp", "w") as f:
		f.write(text)

	############################

	with open("base_files/Antigen.cpp", "r") as f:
		text = f.read()
	with open(nombreP + "/" + "Antigen.cpp", "w") as f:
		f.write(text)

	with open("base_files/Antigen.h", "r") as f:
		text = f.read()
	with open(nombreP + "/" + "Antigen.h", "w") as f:
		f.write(text)

	with open("base_files/Danger.h", "r") as f:
		text = f.read()
	with open(nombreP + "/" + "Danger.h", "w") as f:
		f.write(text)

	with open("base_files/Response.h", "r") as f:
		text = f.read()
	with open(nombreP + "/" + "Response.h", "w") as f:
		f.write(text)

	with open("base_files/Sniffer.h", "r") as f:
		text = f.read()
	with open(nombreP + "/" + "Sniffer.h", "w") as f:
		f.write(text)

	with open("base_files/makefile", "r") as f:
		text = f.read()
	with open(nombreP + "/" + "makefile", "w") as f:
		f.write(text)

	########################

	print("Sistema creado con éxito")

	#except:
	#	print("Se presentó un error en la creación del sistema. Intenlo nuevamente")

def create_system(nCel, namesCell, pobl, ch5, ):
	pass

main()