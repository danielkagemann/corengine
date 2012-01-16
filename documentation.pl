#
# get documentation out of files
#

# define the folders to search for header files
my @folderlist = ('initializers','actions','zones','filter');

# iterate through folders
foreach my $folder (@folderlist) {

	# create output file docs.tpl
	open  OUT, ">doc_$folder.tpl" or die "!: cannot write to file\n";
	print OUT "<h1>$folder</h1>\n";
	
	my $allbuffer = "";
	my $formular  = "{include:tpl/doc_header.tpl}\n<form><select onchange='javascript:window.location.hash=this.options[this.selectedIndex].value'>";
	
	# ignore the base
	my @base = `ls -1 $folder/*base.h`;
	my @list = `ls -1 $folder/*.h | grep -v "base"`;
	
	@list = (@base,@list);
	
	my $unique = 0;
	# iterate through list
	foreach my $file (@list) {
	
		chomp($file);
		print "check file $file...";
		my @content = `grep "/// " $file`;
		
		if ($#content <= 0) {
			print "no documentation\n";
		}
		else {
			print "ok\n";
			
			# first two items always static
			my  $brief = substr ($content[0],4);
			
			if ($content[1] =~ /\/\/\/ _name (.*)/) {
				my  $name  = $1;
				my $buffer = "<a name='cont_$unique'></a>\n<h2>$name</h2>\n";
				$buffer   .= "<em>$brief</em>\n";
				$buffer   .= "<dl id='cont_$unique'>\n";
				
				#iterate through parameters
				for ($i = 2; $i <= $#content; $i++) {
					if ($content[$i] =~ /\/\/\/ _param (.*)/) {
						$param = $1;
						if ($param =~ /<(.+?)> (.*)/) {
							$buffer .= "<dt>&lt;$1&gt;</dt>\n";
							$buffer .= "<dd>$2</dd>\n";
						}
					}
				}
				$buffer .= "</dl>\n";
				$buffer .= "<p>&nbsp;</p>\n";

				# write to file
				$allbuffer .= $buffer;
				$formular  .= "<option value='cont_$unique'>$name</option>";
				
				# increment id
				$unique++;
			}
			else {
				print "invalid documentation (_name)\n";
			}
		}
	}
	
	# close formular data
	$formular .= "</select></form>\n";
	print OUT $formular;
	print OUT $allbuffer;
	
	# close output file
	close OUT;
}


