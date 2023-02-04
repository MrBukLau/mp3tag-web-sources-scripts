# Apple Music Web Sources Script for Mp3tag
[Name]=Apple Music
[BasedOn]=https://music.apple.com
[WordSeparator]=%20
[Encoding]=url-utf-8
[IndexFormat]=%_url%|%_preview%|%_coverurl%|%Title%|%Artist%|%Tracks%|%Kind%|%Explicit%

[ParserScriptIndex]=...

FindLine "<script type=\"application/json\" id=\"serialized-server-data\">"
RegexpReplace ".*<script type=\"application/json\" id=\"serialized-server-data\">\[(.*)\]<\/script>.*" "$1"

json "on" "current"

json_select_object "intent"
	json_select "term"
	If "https://music.apple.com/"
		OutputTo "FallbackItem"
		SayRest
		OutputTo "FallbackTerm"
		Say "Apple Music URL"
		Set "FoundWebURL" "True"
	Else
		OutputTo "FallbackItem"
		Say "https://music.apple.com/"
		json_select "storefront"
		SayRest
		Say "/album/"
		json_select "term"
		SayNextNumber
		json_select "language"
		IfNot ""
			Say "?l="
			SayRest
		EndIf
		OutputTo "FallbackTerm"
		json_select "term"
		Say "Apple Music ID: "
		SayNextNumber
	EndIf
	OutputTo "Output"
json_unselect_object

IfNotOutput "FoundWebURL"
	json_select_object "data"
		json_foreach "sections"
			json_select "id"
			If "search-results-empty-header"
				Set "Output"
				SayOutput "FallbackItem"
				Say "|"
				SayOutput "FallbackItem"
				Say "||"
				SayOutput "FallbackTerm"
				Say "||||"
			Else
				json_select "itemKind"
				IfNot "topSearchLockup"
					json_foreach "items"
						json_select_object "contentDescriptor"
							json_select "kind"

							# Primary
							If "album"
								Set "FoundAlbum" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
							If "song"
								Set "FoundSong" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
							If "musicVideo"
								Set "FoundMusicVideo" "True"

								# %_url%
								json_select "url"
								SayRest
								Say "|"

								# %_preview%
								json_select "url"
								SayRest
								Say "|"

							EndIf
						json_unselect_object

						# Secondary
						IfOutput "FoundAlbum"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select_object "dictionary"
										json_select "url"
										RegexpReplace "(.*)\/.*" "$1"
										SayRest
										Say "/120x120-50.jpeg"
									json_unselect_object
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select_many "titleLinks" "title" " / "
							SayRest
							Say "|"

							# %Artist%
							json_select_many "subtitleLinks" "title" ", "
							SayRest
							Say "|"

							# %Tracks%
							json_select "trackCount"
							SayNextNumber
							Say "|"

							# %Kind%
							Say "Album"
							Say "|"

							# %Explicit%
							json_select "showExplicitBadge"
							If "1"
								Say "Yes"
							EndIf

							SayNewline
							Set "FoundAlbum"

						EndIf
						IfOutput "FoundSong"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select_object "dictionary"
										json_select "url"
										RegexpReplace "(.*)\/.*" "$1"
										SayRest
										Say "/120x120-50.jpeg"
									json_unselect_object
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select "title"
							SayRest
							Say "|"

							# %Artist%
							json_select_many "subtitleLinks" "title" ", "
							SayRest
							Say "|"

							# %Tracks%
							json_select "trackCount"
							Say "|"

							# %Kind%
							Say "Song (Album)"
							Say "|"

							# %Explicit%
							json_select "showExplicitBadge"
							If "1"
								Say "Yes"
							EndIf

							SayNewline
							Set "FoundSong"

						EndIf
						IfOutput "FoundMusicVideo"

							# %_coverurl%
							json_select_object "artwork"
							IfNot ""
									json_select_object "dictionary"
										json_select "url"
										RegexpReplace "(.*)\/.*" "$1"
										SayRest
										Say "/120x120-50.jpeg"
									json_unselect_object
								json_unselect_object
							EndIf
							Say "|"

							# %Title%
							json_select_many "titleLinks" "title" " / "
							SayRest
							Say "|"

							# %Artist%
							json_select_many "subtitleLinks" "title" ", "
							SayRest
							Say "|"

							# %Tracks%
							json_select "trackCount"
							Say "|"

							# %Kind%
							Say "Music Video"
							Say "|"

							# %Explicit%
							json_select "showExplicitBadge"
							If "1"
								Say "Yes"
							EndIf

							SayNewline
							Set "FoundMusicVideo"

						EndIf
					json_foreach_end
				EndIf
			EndIf
		json_foreach_end
	json_unselect_object
Else
	Set "Output"
	SayOutput "FallbackItem"
	Say "|"
	SayOutput "FallbackItem"
	Say "||"
	SayOutput "FallbackTerm"
	Say "||||"
	Set "FoundWebURL"
EndIf

json "off"

[ParserScriptAlbum]=...

FindLine "<script type=\"application/json\" id=\"serialized-server-data\">" 1 1
RegexpReplace ".*<script type=\"application/json\" id=\"serialized-server-data\">\[(.*)\]<\/script>.*" "$1"

json "on" "current"

json_select_object "data"
	IfNot ""
	json_foreach "sections"

		json_select "itemKind"
		If "containerDetailHeaderLockup"
			Set "ValidSection" "True"
		EndIf
		If "trackLockup"
			Set "ValidSection" "True"
		EndIf
		If "containerDetailTracklistFooterLockup"
			Set "ValidSection" "True"
		EndIf
		If "tvMovieDetailHeaderLockup"
			Set "ValidSection" "True"
		EndIf

		IfOutput "ValidSection"
			json_foreach "items"
				# Primary
				json_select_object "contentDescriptor"
					json_select "kind"

					If "album"
						Set "SectionAlbum" "True"

						IfNotOutput "ITUNESALBUMID"
							OutputTo "ITUNESALBUMID"
							json_select_object "identifiers"
								json_select "storeAdamID"
								SayNextNumber
							json_unselect_object
						EndIf

					EndIf

					If "song"
						Set "SectionSong" "True"

						OutputTo "ITUNESMEDIATYPE"
						Say "Normal"
						Say "|"

						OutputTo "ITUNESCATALOGID"
						json_select_object "identifiers"
							json_select "storeAdamID"
							SayNextNumber
						json_unselect_object
						Say "|"

					EndIf

					If "musicVideo"
						Set "SectionSong" "True"

						OutputTo "ITUNESMEDIATYPE"
						Say "Music Video"
						Say "|"

						OutputTo "ITUNESCATALOGID"
						json_select_object "identifiers"
							json_select "storeAdamID"
							SayNextNumber
						json_unselect_object
						Say "|"

					EndIf

				json_unselect_object

				# Secondary
				json_foreach "subtitleLinks"
					IfNot "0"

						IfOutput "SectionAlbum"

							OutputTo "ALBUMARTIST"
							IfOutput "ALBUMARTIST"
								Say ", "
							EndIf
							json_select "title"
							SayRest

							OutputTo "COMPILATION"
							json_select "title"
							IfNot "Various Artists"
								Say "0"
								Say "|"
							EndIf

						EndIf

						IfOutput "SectionSong"

							OutputTo "ARTIST"
							IfOutput "TEMP_ARTIST"
								Say ", "
							EndIf
							json_select "title"
							SayRest
							Set "TEMP_ARTIST" "True"

						EndIf

						json_select_object "segue"
						IfNot ""
							json_select_object "destination"
								json_select_object "contentDescriptor"
									json_select "kind"

									If "artist"
										json_select_object "identifiers"

											IfOutput "SectionAlbum"
												OutputTo "TEMP_ALBUMARTISTID"
												IfOutput "TEMP_ALBUMARTISTID"
													Say "\\\\"
												EndIf
												json_select "storeAdamID"
												SayRest
											EndIf

											IfOutput "SectionSong"
												OutputTo "ITUNESARTISTID"
												IfOutput "TEMP_ITUNESARTISTID"
													Say "\\\\"
												EndIf
												json_select "storeAdamID"
												SayRest
												Set "TEMP_ITUNESARTISTID" "True"
											EndIf

										json_unselect_object
									EndIf

								json_unselect_object
							json_unselect_object
						json_unselect_object
						Else

							IfOutput "SectionAlbum"
								OutputTo "COMPILATION"
								Say "1"
							EndIf

						EndIf

					Else

						IfOutput "SectionSong"
							OutputTo "ARTIST"
							SayOutput "ALBUMARTIST"
							Say "|"
							OutputTo "ITUNESARTISTID"
							SayOutput "TEMP_ALBUMARTISTID"
							Say "|"
						EndIf

					EndIf
				json_foreach_end

				# Cleanup
				IfOutput "TEMP_ARTIST"
					Set "TEMP_ARTIST"
					OutputTo "ARTIST"
					Say "|"
				EndIf
				IfOutput "TEMP_ITUNESARTISTID"
					Set "TEMP_ITUNESARTISTID"
					OutputTo "ITUNESARTISTID"
					Say "|"
				EndIf

				OutputTo "COVERURL"
				json_select_object "artwork"
				IfNot ""
						json_select_object "dictionary"
							json_select "url"
							RegexpReplace "(.*)\/.*" "$1"
							SayRest
							Say "/2000x2000.jpeg"
						json_unselect_object
					json_unselect_object
				EndIf

				# Third
				IfOutput "SectionAlbum"

					OutputTo "ALBUM"
					json_select "title"
					SayRest

					OutputTo "TOTALTRACKS"
					json_select "trackCount"
					SayNextNumber

					OutputTo "COPYRIGHT"
					json_select "description"
					IfNot ""
						RegexpReplace "(?:.*?\\n){2}" ""
						SayRest
					EndIf

				EndIf

				IfOutput "SectionSong"

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

					OutputTo "COMPOSER"
					json_select "composer"
					SayRest
					Say "|"

					OutputTo "DISCNUMBER"
					json_select "discNumber"
					SayNextNumber
					Say "|"

					Set "TOTALDISCS"
					OutputTo "TOTALDISCS"
					json_select "discNumber"
					SayNextNumber

				EndIf

				Set "SectionAlbum"
				Set "SectionSong"

			json_foreach_end
		EndIf
		Set "ValidSection"
	json_foreach_end
	Else
		Set "NoDataFound" "True"
	EndIf
json_unselect_object

json_select_object "data"
IfNot ""
	json_select_object "seoData"
		json_foreach "ogSongs"
			json_select_object "attributes"

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
					Say "|"
				EndIf
				If "Electronic"
					Say "7"
					Say "|"
				EndIf
				If "Electronica"
					Say "1058"
					Say "|"
				EndIf
				If "Singer/Songwriter"
					Say "10"
					Say "|"
				EndIf
				If "Pop"
					Say "14"
					Say "|"
				EndIf
				If "R&B/Soul"
					Say "15"
					Say "|"
				EndIf
				If "Soundtrack"
					Say "16"
					Say "|"
				EndIf
				If "Dance"
					Say "17"
					Say "|"
				EndIf
				If "House"
					Say "1048"
					Say "|"
				EndIf
				If "Hip-Hop/Rap"
					Say "18"
					Say "|"
				EndIf
				If "Worldwide"
					Say "19"
					Say "|"
				EndIf
				If "Alternative"
					Say "20"
					Say "|"
				EndIf
				If "Rock"
					Say "21"
					Say "|"
				EndIf
				If "J-Pop"
					Say "27"
					Say "|"
				EndIf
				If "Anime"
					Say "29"
					Say "|"
				EndIf
				If "K-Pop"
					Say "51"
					Say "|"
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

			OutputTo "ITUNESCOMPOSERID"
			json_select_object "relationships"
				json_select_object "composers"
					json_select_many "data" "id" "\\\\"
					SayRest
				json_unselect_object
			json_unselect_object
			Say "|"

		json_foreach_end

	json_unselect_object
	EndIf
json_unselect_object

# Extra Apple Music Tags
OutputTo "ITUNESGAPLESS"
Say "0"
Say "|"

OutputTo "ITUNESCOUNTRYID"
Say "143441"
Say "|"

#OutputTo "ITUNESACCOUNT"
#Say "CHANGE_TO_YOUR_EMAIL_ADDRESS"
#Say "|"

#OutputTo "ITUNESOWNER"
#Say "CHANGE_TO_YOUR_NAME"
#Say "|"

#OutputTo "ITUNESPURCHASEDATE"
#Say "0000-00-00 00:00:00"
#Say "|"

# Cleanup
Set "TEMP_ALBUMARTISTID"

IfOutput "NoDataFound"
	Set "Output"
EndIf

json "off"
