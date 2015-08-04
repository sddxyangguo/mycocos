#!/bin/perl 
use strict;


my $file="myhero.json";
open("LOG","$file") or die;

foreach(<LOG>)
{
	if(/(^.+inttag":\d\d,.+,"positionX":)(\d+)(,"positionY":)(\d+)(,.+)$/)
	{
		my $num1=$2."0";
		my $num2=$4."0";
		print "$1$num1$3$num2$5\n";
	}else{
		print;
	}
}