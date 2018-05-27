#!/usr/bin/env bash

function check {
	SECURITY=(1 0 0);

	if [ `stat -c%s $1` -eq 0 ]; then
		SECURITY[0]=0;
	else
		CHECK_FILE=$1;
		I=0
		while read; do
			I=$(($I + 1))
			if [ $I -eq 1 ]; then
				if [[ $REPLY =~ "#!/usr/bin/perl" ]]; then
  					SECURITY[1]=1;
				elif [[ $REPLY =~ "#!/usr/bin/env perl" ]]; then
  					SECURITY[1]=1;
				elif [[ $REPLY =~ "#!/path/to/python" ]]; then
  					SECURITY[1]=1;
				elif [[ $REPLY =~ "#!/path/to/env python" ]]; then
  					SECURITY[1]=1;
				fi
			elif [ $(echo -e `expr "$REPLY" : 'print'`) -eq 5 ]; then
				SECURITY[2]=1;
			fi
		done < "$CHECK_FILE"
	fi

	case ${SECURITY[0]} in
		0) echo -n " > Pusty plik!" >>  RAPORT.txt;;
		1) echo -n "" ;;
	esac

if [ ${SECURITY[1]} -eq 0 ]; then
	echo -n " Nie dzialajacy skrypt" >> RAPORT.txt;
elif [ ${SECURITY[2]} -eq 0 ]; then
	echo -n " Plik wydaje sie podejrzany. Sprawdz jego dzialanie. <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" >> RAPORT.txt;
fi

echo "" >> RAPORT.txt;
}

if [ $# = 0 -o 1 -lt $# ]; then
	echo "Bledne wywolanie! Sprawdz opcje wywolania poprzez komende -h [help]";
	exit 1;
elif [ $1 = "-h" ]; then
	echo -e "\nNAZWA\n\tszumski-bash.sh - sprawdzanie skryptow [perl/python]\nSKLADNIA\n\tszumski-bash.sh [opcja]\nOPIS\n\tSkrypt pobiera od uzytkownika poprzez parametr wywolania adres \n\tkatalogu roku. W owym katalogu powinny znajdowac sie podkatalogi \n\tstudentow (a \tw nich znajdujace sie skrypty). Sprawdz wyglad danych\n\ttestowych. Pliki studenta sa weryfikowane pod trzema wzgledami. Pierwsza\n\tto czy plik jest pusty. Drugie kryterium czy pierwsza linijka zawiera\n\tdane interpretatora, wreszcie trzecia czy skrypt cos wypisuje na\n\tstandardowe wyjscie. Oczywiscie tych danych jak i kazdych tajnych\n\tnalezy nie podawac nikomu poniewaz skrypt stanie sie latwym do zlamania.\n\tPo zakonczeniu pracy program tworzy raport dla \tsprawdzajacego\nOPCJE\n\t-h [help] pomoc / instrukcja obslugi\n\tsciezka do katalogu roku (przyklad: szumski-bash.sh ZIMA_2012)\nWERSJA\n\t1.0\n";
	exit 0;
fi

if [ ! -d $1 ]; then
	echo "Wpisany plik nie jest katalogiem!";
	exit 1;
elif [ ! -s $1 ]; then
	echo "Katalog jest pusty! (Wprowadz skrypty studentow)";
	exit 1;
fi

echo -e "\nBadane skrypty studentow: \n";
`echo ls -B -1 --color $1`

touch tmp.txt;
`echo ls -B -1 $1` > tmp.txt;

echo -e "Raport $1 `date +"%m-%d-%y"`\n\n" > RAPORT.txt;
echo -e "Laczna waga katalogu: `du -s -h`\n\n" >> RAPORT.txt;
FILE="tmp.txt";
I=0
while read; do
	I=$(($I + 1))
	`echo ls -B -1 $1/$REPLY` > $1/$REPLY/tmp2.txt;
	ILOSC_PLIKOW=`ls -B $1/$REPLY/ | wc -l | tr -d ' '`;
	ILOSC_PLIKOW_WSZYSTKICH=`ls $1/$REPLY/ | wc -l | tr -d ' '`;
	ILOSC_PLIKOW_TYMCZASOWYCH=$((ILOSC_PLIKOW_WSZYSTKICH-ILOSC_PLIKOW));
	ILOSC_PLIKOW=$((ILOSC_PLIKOW-1));
	echo "$1/$REPLY/ Ilosc plikow: $ILOSC_PLIKOW, Kopii_roboczych (z ~): $ILOSC_PLIKOW_TYMCZASOWYCH" >> RAPORT.txt;
	PRE="$1/$REPLY/";
	FILE2="$1/$REPLY/tmp2.txt"
	J=0
	while read; do
		J=$(($J + 1));
		if [ $REPLY != "tmp2.txt" ]; then
   			echo -e -n "\t$REPLY" >> RAPORT.txt;
			check "$PRE$REPLY";
		fi
	done < "$FILE2"
done < "$FILE"

while true; do
	read -p "Utworzono plik z raportem: RAPORT.txt. Otworzyc? (T/N): " QUE;
	if [ $QUE = "T" -o $QUE = "t" ]; then
		`gedit RAPORT.txt`
		break;
	fi
	if [ $QUE = "N" -o $QUE = "n" ]; then
		echo "Plik zapisany RAPORT.txt";
		break;
	fi
done

FILE="tmp.txt";
I=0
while read; do
	I=$(($I + 1))
	rm $1$REPLY/tmp2.txt;
done < "$FILE"

rm tmp.txt;
exit 0;
