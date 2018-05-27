package Ebug;
use strict;
use base "Exporter";
use feature qw/switch/;
our @EXPORT = qw/err/;

sub err {
	my($bug) = @_; 

	given($bug) {
		when(0) { print "Nie podales argumentow nazwy serwisu oraz hasla ktore maja zostac zapisane\n" }
		when(1) { print "Podana przez Ciebie nazwa serwisu istnieje juz w Twojej bazie, jesli trzeba mozesz zmienic haslo\n" }
		when(2) { print "Nie podales nazwy portalu ktory ma zostac usuniety z Twojej bazy stron\n" }
		when(3) { print "Twoja baza nie zawiera zadnych serwisow. Nie ma co usuwac.\n" }
		when(4) { print "Nie usunieto serwisu (nie znaleziono pasujacego wzorca)\n" }
		when(5) { print "Nie podales nazwy portalu do ktorego chcesz zobaczyc haslo\n" }
		when(6) { print "Nie znaleziono serwisu ;(\n" }
		when(7) { print "Nie podales nazwy portalu do ktorego chcesz zmienic haslo\n" }
		when(8) { print "Nie zmieniono hasla (nie znaleziono pasujacego wzorca)\n" }
	}
}

1;