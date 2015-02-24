#!/usr/bin/perl
use strict;
# usage : totPDBfile   partPDBfile 
## print shortest distance of gene

my $input    = $ARGV[0];
open(RD, "< ${input}") || die "Not Found file1: $!\n";

my @token=();

my $i=0;

my $Rtot=0.0;
my $Ru=0.0; ## unify
my $Rc=0.0; ## classify

my $bufMin;
my $RuMin=10000;
print "   num  Rwork    Rfree    Rinner   Ru   Rc \n";
while (my $buf = <RD>){
	$buf =~ s/\n//;
	@token = split(/\s\s*/, $buf);
	#@token = split(/  */, $buf);

	#$Rtot=$token[2]*$token[3]*$token[4]*1000;
	$Ru=($token[2]+$token[3])/2;
	$Rc=($token[2]-$token[3])/2;
	if ( $RuMin >= $Ru ) {
		$RuMin = $Ru;
		$bufMin = $buf;
	} 
	#print "1=$token[2] 2=$token[3] 3=$token[4]\n";
	printf ("%s  %.4f  %.4f\n",$buf,$Ru,$Rc);
	$i++;
}

	printf ("==Ru Min=== \n");
	printf ("%s  %.4f  \n",$bufMin,$RuMin);




