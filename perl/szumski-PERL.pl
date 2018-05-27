#!/usr/bin/env perl

use feature qw/switch/;
use Ebug qw/err/;

if ( $ARGV[0] eq "-h" ) {
	print "\nNAZWA\n\tszumski-PERL.pl - ksiazka przechowujaca hasla do stron www\nSKLADNIA\n\tszumski-PERL.pl [1] [2] [3]\nOPIS\n\tW dobie ciaglego rozwoju Internetu kazdy z nas ma problem z \n\tzapamietaniem wielu hasel do swoich ulubionych witryn www. Z pomoca \n\tprzychodzi skrypt szumski-PERL.pl pozwalajacy na sprawne poruszanie sie \n\tw swojej bazie witryn / hasel\nOPCJE\n\t[1] [2] [3]\n\n\t[1] + dodanie serwisu do ksiazki\n\t    - usuniecie portalu\n\t    ? listowanie ksiazki\n\t    -see zobaczenie hasla wybranego serwisu www\n\t    -modify zmiana hasla\n\t    -h plik pomocy\n\t[2] nazwa portalu www\n\t[3] haslo\nDODATKOWE UWAGI\n\tSkrypt w zaden sposob nie gwarantuje bezpieczne przechowywanie hasla. \n\tJest ono w latwy sposob do przechwycenia. Skrypt nalezy przechowywac we \n\twzglednie bezpiecznym miejscu aby nie zagrozic bezpieczenstwu swoich \n\thasel.\nWERSJA\n\t1.0\n\n";
	exit 0
}

if ( ! -e "data.dat" ) {
	print "Nie znalazlem pliku z danymi stworzylem nowy\n";
	`touch data.dat`
}

sub space {
              my($check) = @_;
              
              if ($check =~ / /) {
                    print "Parametr $check zawiera spacje!\n";
                    exit 1
              }
}

open(FILE, "data.dat") || die("Blad czytania pliku\n");
@txt = <FILE>;
close(FILE);

given($ARGV[0]) {
	when ("+") {
		if ( $ARGV[1] eq "" || $ARGV[2] eq "" ) {
			err(0);
			exit 1
		}
			
                    space($ARGV[1]);         
		space($ARGV[2]);
				
		foreach $line (@txt) {
			my @val = split(' ', $line);
        		if($val[0] =~ /\b$ARGV[1]\b/) {
				err(1);
				exit 1
			}
		}		

		open(FILE, '>>', 'data.dat') or die "Nie można otworzyć pliku: $!";
		print FILE "$ARGV[1] $ARGV[2]\n";
		close(FILE);

		print "Poprawnie wprowadzono nowy serwis\n";
	}
	when ("-") {
		if ( $ARGV[1] eq "" ) {
			err(2);
			exit 1
		}
		elsif ( -s "data.dat" == 0 ) {
			err(3);
			exit 1
		}

		space($ARGV[1]);

		$delete = 0;

		foreach $line (@txt) {
			my @val = split(' ', $line);
        		if($val[0] =~ /\b$ARGV[1]\b/) {
				$delete = 1;
			}
			else {
				`echo -n "$line" >> tmp.txt`
			}
		}

		if ($delete == 1) {
			if ( ! -e "tmp.txt" ) {
				`echo "" > tmp.txt`
			}
			unlink "data.dat";
			rename "tmp.txt", "data.dat";
			print "Poprawnie usunieto\n"
		}
		else {
			err(4);
			unlink "tmp.txt";
			exit 1
		}
	}
	when ("?") {
		print "\nSerwisy zapisane w bazie:\n\n";
		foreach $line (@txt) {
			my @val = split(' ', $line);
			print "$val[0]\n"
		}
		print "\n"
	}
	when ("-see") {
		if ( $ARGV[1] eq "" ) {
			err(5);
			exit 1
		}

		space($ARGV[1]);		

		foreach $line (@txt) {
			my @val = split(' ', $line);
			if ($val[0] =~ /\b$ARGV[1]\b/) {
				$val[1] =~ s/[\s]+/_/g;    
				print "\nTwoje haslo to: $val[1]\n\n";
				exit 0
			}
		}
		err(6);
		exit 1
	}
	when ("-modify") {
		if ( $ARGV[1] eq "" ) {
			err(7);
			exit 1
		}

                    space($ARGV[1]);

		print "\nPodaj stare haslo: ";
		$old_pass = <STDIN>;
		space($old_pass);
		print "Podaj nowe haslo: ";
		$new_pass = <STDIN>;
		space($new_pass);

		$modify = 0;
		foreach $line (@txt) {
			my @val = split(' ', $line);
			if ($val[0] =~ /\b$ARGV[1]\b/) {
				if ($val[1] == $old_pass) {
					`echo -n "$val[0] $new_pass" >> tmp.txt`;
					$modify = 1;
				}
			}
			else {
				`echo -n "$line" >> tmp.txt`
			}
		}
		if ($modify == 1) {
			if ( ! -e "tmp.txt" ) {
				`echo "" > tmp.txt`
			}
			unlink "data.dat";
			rename "tmp.txt", "data.dat";
			print "Zmieniono pomyslnie\n";
		}
		else {
			err(8);
			unlink "tmp.txt";
			exit 1
		}
	}
}

exit 0