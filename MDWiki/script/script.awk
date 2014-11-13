BEGIN {
	FS="%title%|%root_path%|%content%"
}

{
	if(/%root_path%/) {
		print $1 ROOT_PATH $2
	}
	else if(/%title%/) {
		print $1 TITLE $2
	}
	else if(/%content%/) {
		print $1 CONTENT $2
	}
	else {
		print 
	}
}
