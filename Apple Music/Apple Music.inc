# Apple Music Web Sources Script for Mp3tag
[Name]=Apple Music
[BasedOn]=https://itunes.apple.com/
[WordSeparator]=%20
[IndexFormat]=%_url%|%Artist%|%Album%|%_preview%|%Version%|%Tracks%|%Copyright%|%Store%|%Year%|%Genre%
[Encoding]=url-utf-8

# Index albums
[ParserScriptIndex]=...

# debug "on" "C:\debug-index.txt"
# DebugWriteInput "C:\debug-index-in.txt"

# Turn on JSON parsing
json "on"

# Number of items
json_select "resultCount"
IfNot "0"
	# Parse all items
	json_foreach "results"
	# Check for album
	json_select "collectionType"
	If "Album"
		# Album URL
		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		SayRest
		Say "|"
		# Artist
		json_select "artistName"
		SayRest
		Say "|"
		# Album
		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		SayRest
		Say "|"
		# Preview URL
		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		SayRest
		Say "|"
		# Version
		json_select "collectionExplicitness"
		Replace "notExplicit" ""
		Replace "explicit" "Explicit"
		Replace "cleaned" "Cleaned"
		SayRest
		Say "|"
		# Track count
		json_select "trackCount"
		SayNextNumber
		Say "|"
		# Copyright
		json_select "copyright"
		SayRest
		Say "|"
		# Store
		json_select "country"
		SayRest
		Say "|"
		# Store
		json_select "releaseDate"
		SayNextNumber
		Say "|"
		# Genre
		json_select "primaryGenreName"
		SayRest
		SayNewline
	EndIf
	json_foreach_end
EndIf

# Get album
[ParserScriptAlbum]=...

# debug "on" "C:\debug-album.txt"
# DebugWriteInput "C:\debug-album-in.txt"

# Turn on JSON parsing and clean data
FindLine "<script type=\"fastboot/shoebox\" id=\"shoebox-media-api-cache-amp-music\">"
FindInLine "<script type=\"fastboot/shoebox\" id=\"shoebox-media-api-cache-amp-music\">"
RegexpReplace "(?i).*?id=\"shoebox-media-api-cache-amp-music\">(\{.*\"\})<\/script>.+" "$1"
Replace "\\\\\\\"" "\u0022"
Replace "\\\"" "\""
Replace "\":\"{" "\":{"
Replace "}}]}\"" "}}]}"
Replace "]}}}]}\"}" "]}}}]}}"
RegexpReplace "\.catalog\.(.*?)\.albums\.(.*?)\.art" "mp3tagalbum"
Replace ".5burl.5d.f.extend.5balbums.5d.editorialartwork.extend.offers" ""
Replace ".2cpopularity.2ceditorialvideo.fields.5balbums.3aalbums.5d.artistname" ""
Replace ".2cartisturl.2cartwork.2ceditorialartwork.2cname.2cplayparams.2creleasedate" ""
Replace ".2curl.fields.5bartists.5d.name.2curl.fields.5brecord-labels" ""
Replace ".5d.name.2curl.include.5bsongs.5d.artists.2ccomposers.include.tracks" ""
RegexpReplace "2crecord-labels\.l\.(.*?)\.omit" "locale"
Replace ".2cartists.locale.5bresource" ""
# Replace ".2cartists.2crecord-labels.l.en-us.omit.5bresource" ""
Replace ".5d.autos.views.appears-on.2cmore-by-artist.2crelated-videos" ""
Replace ".2cother-versions.2cyou-might-also-like.2cvideo-extras.2caudio-extras" ""

debug "on" "C:\debug-album.txt"
DebugWriteInput "C:\debug-album-in.txt"

RegexpReplace "storefronts\.(.*?)\"" "storefronts\""

json "on" "current"

# List supported store languages
#json_select_object ".storefronts"
#json_select_array "d" 1
#json_select "attributes"
#json_select "defaultLanguageTag"
#OutputTo "DEFAULTLANGUAGE"
#SayRest
#json_select_array "supportedLanguageTags" -1 ", "
#IfNot ""
#OutputTo "SUPPORTEDLANGUAGES"
#SayRest
#EndIf

json_unselect_object
json_select "mp3tagalbum"
json_select_array "d" 1
json_select "type"
If "albums"
	json_select_object "attributes"
		json_select_object "artwork"
			json_select "url"
			IfNot ""
				Replace "{w}" "2000"
				Replace "{h}" "2000"
				Replace "{f}" "jpeg"
				OutputTo "COVERURL"
				SayRest
			EndIf
		json_unselect_object
		json_select "artistName"
		OutputTo "ALBUMARTIST"
		SayRest
		json_select "name"
		OutputTo "ALBUM"
		SayRest
		json_select "copyright"
		OutputTo "COPYRIGHT"
		SayRest
		json_select "isCompilation"
		OutputTo "COMPILATION"
		SayRest
	json_unselect_object
	json_select_object "relationships"
		json_select_object "tracks"
			json_foreach "data"
				json_select "type"
				If "songs"
					json_select "id"
					OutputTo "ITUNESCATALOGID"
					SayNextNumber
					Say "|"
					json_select_object "attributes"
						json_select "artistName"
						OutputTo "ARTIST"
						SayRest
						Say "|"					
						json_select "discNumber"
						OutputTo "DISCNUMBER"
						SayNextNumber
						Say "|"					
						json_select_array "genreNames" 1
						OutputTo "GENRE"
						SayRest
						Say "|"
						json_select "durationInMillis"
						OutputTo "_LENGTH"
						SayNextNumber
						Say "|"
						json_select "releaseDate"
						OutputTo "YEAR"
						SayRest
						Say "|"
						json_select "name"
						OutputTo "TRACKS"
						SayRest
						Say "|"
						json_select "isrc"
						OutputTo "ISRC"
						SayRest
						Say "|"
						json_select "trackNumber"
						OutputTo "TRACK"
						SayNextNumber
						Say "|"					
						json_select "composerName"
						OutputTo "COMPOSER"
						SayRest
						Say "|"
						json_select "contentRating"
						OutputTo "ITUNESADVISORY"
						IfNot ""
							Replace "notExplicit" "0"
							Replace "explicit" "1"
							Replace "cleaned" "2"
							SayRest
						Else
							Say "0"
						EndIf
						Say "|"
						json_select "playParams"
						IfNot ""
							json_select "kind"
							If "song"
								OutputTo "ITUNESMEDIATYPE"
								Replace "song" "Normal"
								Say "|"
							EndIf
						EndIf
						Say "|"
					json_unselect_object
				EndIf
			json_foreach_end
		json_unselect_object
	json_unselect_object
EndIf
