# Apple Music Web Sources Script for Mp3tag
[Name]=Apple Music
[BasedOn]=https://itunes.apple.com/
[AlbumUrl]=
[WordSeparator]=+
[IndexFormat]=%_url%|%Artist%|%Album%|%_preview%|%Version%|%Tracks%|%Collection ID%|%Copyright%|%Store%|%Currency%|%Price%|%Year%|%Genre%
[Encoding]=url-utf-8

[ParserScriptIndex]=...

json "on"

json_select "resultCount"
IfNot "0"
	json_foreach "results"
	json_select "collectionType"
	If "Album"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "artistName"
		SayRest
		Say "|"

		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		SayRest
		Say "|"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "collectionExplicitness"
		Replace "notExplicit" ""
		Replace "explicit" "Explicit"
		Replace "cleaned" "Cleaned"
		SayRest
		Say "|"

		json_select "trackCount"
		SayNextNumber
		Say "|"

		json_select "collectionId"
		SayNextNumber
		Say "|"

		json_select "copyright"
		SayRest
		Say "|"

		json_select "country"
		SayRest
		Say "|"

		json_select "currency"
		SayRest
		Say "|"

		json_select "collectionPrice"
		SayRest
		Say "|"

		json_select "releaseDate"
		SayNextNumber
		Say "|"

		json_select "primaryGenreName"
		SayRest
		SayNewline

	EndIf
	If "Compilation"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "artistName"
		SayRest
		Say "|"

		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		SayRest
		Say "|"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "collectionExplicitness"
		Replace "notExplicit" "C"
		Replace "explicit" "C Explicit"
		Replace "cleaned" "C Cleaned"
		SayRest
		Say "|"

		json_select "trackCount"
		SayNextNumber
		Say "|"

		json_select "collectionId"
		SayNextNumber
		Say "|"

		json_select "copyright"
		SayRest
		Say "|"

		json_select "country"
		SayRest
		Say "|"

		json_select "currency"
		SayRest
		Say "|"

		json_select "collectionPrice"
		SayRest
		Say "|"

		json_select "releaseDate"
		SayNextNumber
		Say "|"

		json_select "primaryGenreName"
		SayRest
		SayNewline

	EndIf
	json_foreach_end
EndIf

[ParserScriptAlbum]=...

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
Replace ".2cpopularity" ""
Replace ".2ceditorialvideo.fields.5balbums.3aalbums.5d.artistname" ""
Replace ".2cartisturl.2cartwork" ""
Replace ".2ccontentrating.2ceditorialartwork" ""
Replace ".2ceditorialnotes" ""
Replace ".2cname.2cplayparams.2creleasedate" ""
Replace ".2curl.fields.5bartists.5d.name.2curl.fields.5brecord-labels" ""
Replace ".5d.name.2curl.include" ""
Replace ".5bmusic-videos.5d.artists.2ccomposers.include" ""
Replace ".5bsongs.5d.artists.2ccomposers.include.tracks" ""
RegexpReplace "2crecord-labels\.l\.(.*?)\.omit" "locale"
Replace ".2cartists.locale.5bresource" ""
Replace ".5d.autos.views.appears-on.2cmore-by-artist.2crelated-videos" ""
Replace ".2cother-versions.2cyou-might-also-like.2cvideo-extras.2caudio-extras" ""
Replace ".5d.autos.platform.web.views.appears-on.2cmore-by-artist.2crelated-videos" ""

RegexpReplace "storefronts\.(.*?)\"" "storefronts\""

json "on" "current"

json_select "mp3tagalbum"
json_select_array "d" 1
json_select "type"
If "albums"

	json_select "id"
	OutputTo "ITUNESALBUMID"
	SayRest

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

		json_select "artistName"
		If "Various Artists"
			OutputTo "COMPILATION"
			Say "1"
		Else
			OutputTo "COMPILATION"
			Say "0"
		EndIf

#		json_select "recordLabel"
#		OutputTo "LABEL"
#		SayRest
#		Say "|"

#		json_select "trackCount"
#		OutputTo "TOTALTRACKS"
#		SayNextNumber
#		Say "|"

#		json_select "upc"
#		OutputTo "UPC"
#		SayRest
#		Say "|"

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

						json_select "discNumber"
						Set "TOTALDISCS"
						OutputTo "TOTALDISCS"
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
						OutputTo "XID"
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

						json_select_array "genreNames" 1
						If "Country"
							OutputTo "ITUNESGENREID"
							Say "6"
							Say "|"
						EndIf
						If "Electronic"
							OutputTo "ITUNESGENREID"
							Say "7"
							Say "|"
						EndIf
						If "Electronica"
							OutputTo "ITUNESGENREID"
							Say "1058"
							Say "|"
						EndIf
						If "Singer/Songwriter"
							OutputTo "ITUNESGENREID"
							Say "10"
							Say "|"
						EndIf
						If "Pop"
							OutputTo "ITUNESGENREID"
							Say "14"
							Say "|"
						EndIf
						If "R&B/Soul"
							OutputTo "ITUNESGENREID"
							Say "15"
							Say "|"
						EndIf
						If "Soundtrack"
							OutputTo "ITUNESGENREID"
							Say "16"
							Say "|"
						EndIf
						If "Dance"
							OutputTo "ITUNESGENREID"
							Say "17"
							Say "|"
						EndIf
						If "House"
							OutputTo "ITUNESGENREID"
							Say "1048"
							Say "|"
						EndIf
						If "Hip-Hop/Rap"
							OutputTo "ITUNESGENREID"
							Say "18"
							Say "|"
						EndIf
						If "Worldwide"
							OutputTo "ITUNESGENREID"
							Say "19"
							Say "|"
						EndIf
						If "Alternative"
							OutputTo "ITUNESGENREID"
							Say "20"
							Say "|"
						EndIf
						If "Rock"
							OutputTo "ITUNESGENREID"
							Say "21"
							Say "|"
						EndIf
						If "J-Pop"
							OutputTo "ITUNESGENREID"
							Say "27"
							Say "|"
						EndIf
						If "Anime"
							OutputTo "ITUNESGENREID"
							Say "29"
							Say "|"
						EndIf
						If "K-Pop"
							OutputTo "ITUNESGENREID"
							Say "51"
							Say "|"
						EndIf

					json_unselect_object
					json_select_object "relationships"

						json_select_object "composers"
							json_foreach "data"
								IfNot "0"
									json_foreach_end
									json_select_object "relationships"
									json_select_object "composers"
									json_select_array "data" 1
										json_select "id"
										OutputTo "ITUNESCOMPOSERID"
										SayRest
									json_unselect_object
								Else
									json_foreach_end
								EndIf
							OutputTo "ITUNESCOMPOSERID"
							Say "|"
						json_unselect_object

						json_select_object "artists"
							json_foreach "data"
								IfNot "0"
									json_foreach_end
									json_select_object "relationships"
									json_select_object "artists"
									json_select_array "data" 1
										json_select "id"
										OutputTo "ITUNESARTISTID"
										SayRest
									json_unselect_object
								Else
									json_foreach_end
								EndIf
							OutputTo "ITUNESARTISTID"
							Say "|"
						json_unselect_object

					json_unselect_object

					OutputTo "ITUNESGAPLESS"
					Say "0"
					Say "|"

					OutputTo "ITUNESMEDIATYPE"
					Say "Normal"
					Say "|"

					OutputTo "ITUNESCOUNTRYID"
					Say "143441"
					Say "|"

#					OutputTo "ITUNESACCOUNT"
#					Say "CHANGETOEMAILADDRESS"
#					Say "|"

#					OutputTo "ITUNESOWNER"
#					Say "CHANGETONAME"
#					Say "|"

#					OutputTo "ITUNESPURCHASEDATE"
#					Say "0000-00-00 00:00:00"
#					Say "|"

				EndIf
			json_foreach_end
		json_unselect_object
	json_unselect_object
EndIf
