# Apple Music Web Sources Script for Mp3tag
[Name]=Apple Music
[BasedOn]=https://music.apple.com/
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

FindLine "<script type=\"application/json\" id=\"serialized-server-data\">"

RegexpReplace ".*<script type=\"application/json\" id=\"serialized-server-data\">\[(.*)\]<\/script>.*" "$1"

json "on" "current"

json_select_object "intent"
IfNot ""
	json_select_object "contentDescriptor"
	IfNot ""
		json_select "kind"
		If "album"
			json_select_object "identifiers"
			IfNot ""
				json_select "storeAdamID"
				IfNot ""
					OutputTo "ITUNESALBUMID"
					SayRest
				EndIf
				json_unselect_object
			EndIf
		EndIf
		json_unselect_object
	EndIf
	json_unselect_object
EndIf

json_select_object "data"
IfNot ""
	json_foreach "sections"

		json_select "itemKind"
		If "containerDetailHeaderLockup"
			json_foreach "items"

				json_select_object "artwork"
				IfNot ""
					json_select_object "dictionary"
					IfNot ""
						json_select "url"
						IfNot ""
							Replace "{w}" "2000"
							Replace "{h}" "2000"
							Replace "{f}" "jpeg"
							OutputTo "COVERURL"
							SayRest
						EndIf
						json_unselect_object
					EndIf
					json_unselect_object
				EndIf

				OutputTo "ALBUM"
				json_select "title"
				SayRest

				json_foreach "subtitleLinks"
					json_select_object "segue"
					IfNot ""
						json_select_object "destination"
						IfNot ""
							json_select_object "contentDescriptor"
							IfNot ""
								json_select "kind"
								If "artist"
									json_select_object "identifiers"
									IfNot ""
										json_select "storeAdamID"
										OutputTo "ITUNESARTISTID"
										SayRest
										Say "|"
										json_unselect_object
									EndIf
								EndIf
								json_unselect_object
							EndIf
							json_unselect_object
						EndIf
						json_unselect_object
					Else
						Set "COMPILATION"
						OutputTo "COMPILATION"
						Say "1"
					EndIf
				json_foreach_end

				OutputTo "TOTALTRACKS"
				json_select "trackCount"
				SayNextNumber

			json_foreach_end
		EndIf

		If "containerDetailTracklistFooterLockup"
			json_foreach "items"

				OutputTo "COPYRIGHT"
				json_select "description"
				SayRegexp "℗.*"
				If ""
					json_select "description"
					SayRegexp "©.*"
				EndIf

			json_foreach_end
		EndIf

		If "trackLockup"
			json_foreach "items"

				OutputTo "TRACKS"
				json_select "title"
				SayRest
				Say "|"

				OutputTo "TRACK"
				json_select "trackNumber"
				SayNextNumber
				Say "|"

				OutputTo "_LENGTH"
				json_select "duration"
				SayNextNumber
				Say "|"

				json_select_object "contentDescriptor"
				IfNot ""
					json_select "kind"
					OutputTo "ITUNESMEDIATYPE"
					If "song"
						Say "Normal"
					EndIf
					If "musicVideo"
						Say "Music Video"
					EndIf
					json_select_object "identifiers"
					IfNot ""
						OutputTo "ITUNESCATALOGID"
						json_select "storeAdamID"
						SayRest
						json_unselect_object
					EndIf
					json_unselect_object
				EndIf
				OutputTo "ITUNESMEDIATYPE"
				Say "|"
				OutputTo "ITUNESCATALOGID"
				Say "|"

				json_foreach "subtitleLinks"
					json_select_object "segue"
					IfNot ""
						json_select_object "destination"
						IfNot ""
							json_select_object "contentDescriptor"
							IfNot ""
								json_select "kind"
								If "artist"
									json_select_object "identifiers"
									IfNot ""
										json_select "storeAdamID"
										OutputTo "ITUNESARTISTID"
										SayRest
										Say "|"
										json_unselect_object
									EndIf
								EndIf
								json_unselect_object
							EndIf
							json_unselect_object
						EndIf
						json_unselect_object
					EndIf
				json_foreach_end
				OutputTo "ITUNESARTISTID"
				Say "|"

				OutputTo "COMPOSER"
				json_select "composer"
				SayRest
				Say "|"

				OutputTo "DISCNUMBER"
				json_select "discNumber"
				SayNextNumber
				Say "|"

				OutputTo "TOTALDISCS"
				json_select "discNumber"
				Set "TOTALDISCS"
				SayNextNumber

				OutputTo "ARTIST"
				json_select "artistName"
				SayRest
				Say "|"

				OutputTo "ALBUMARTIST"
				json_select "containerArtistName"
				SayRest
				Say "|"

				OutputTo "COMPILATION"
				json_select "containerArtistName"
				IfNot "Various Artists"
					Say "0"
				EndIf

				OutputTo "ITUNESGAPLESS"
				Say "0"

				OutputTo "ITUNESCOUNTRYID"
				Say "143441"

#				OutputTo "ITUNESACCOUNT"
#				Say "CHANGETOYOUREMAILADDRESS"

#				OutputTo "ITUNESOWNER"
#				Say "CHANGETOYOURNAME"

#				OutputTo "ITUNESPURCHASEDATE"
#				Say "0000-00-00 00:00:00"

			json_foreach_end
		EndIf

	json_foreach_end

	json_select_object "data"

	json_select_object "seoData"
	IfNot ""

		json_foreach "ogSongs"
			json_select_object "attributes"
			IfNot ""
				OutputTo "YEAR"
				json_select "releaseDate"
				SayRest
				Say "|"

				OutputTo "XID"
				json_select "isrc"
				SayRest
				Say "|"

				OutputTo "GENRE"
				json_select_array "genreNames" 1
				SayRest
				Say "|"

				OutputTo "ITUNESGENREID"
				json_select_array "genreNames" 1
				If "Country"
					Say "6"
				EndIf
				If "Electronic"
					Say "7"
				EndIf
				If "Electronica"
					Say "1058"
				EndIf
				If "Singer/Songwriter"
					Say "10"
				EndIf
				If "Pop"
					Say "14"
				EndIf
				If "R&B/Soul"
					Say "15"
				EndIf
				If "Soundtrack"
					Say "16"
				EndIf
				If "Dance"
					Say "17"
				EndIf
				If "House"
					Say "1048"
				EndIf
				If "Hip-Hop/Rap"
					Say "18"
				EndIf
				If "Worldwide"
					Say "19"
				EndIf
				If "Alternative"
					Say "20"
				EndIf
				If "Rock"
					Say "21"
				EndIf
				If "J-Pop"
					Say "27"
				EndIf
				If "Anime"
					Say "29"
				EndIf
				If "K-Pop"
					Say "51"
				EndIf

				OutputTo "ITUNESADVISORY"
				json_select "contentRating"
				IfNot ""
					Replace "notExplicit" "0"
					Replace "explicit" "1"
					Replace "cleaned" "2"
					Replace "clean" "2"
					SayRest
				Else
					Say "0"
				EndIf
				Say "|"

				json_unselect_object
			EndIf
		json_foreach_end

		json_unselect_object
	EndIf

	json_unselect_object
EndIf
