//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2020 Douglas Mark Royer, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO DOUGLAS MARK ROYER
// THIS CODE IS PROPERTY OF THE COPYRIGHT HOLDER AND IS NOT TO
// BE DIVULGED OR USED BY PARTIES WHO HAVE NOT RECEIVED WRITTEN
// AUTHORIZATION FROM THE OWNER.
//
// THIS SOFTWARE AND MANUAL ARE BOTH PROTECTED BY UNITED STATES
// COPYRIGHT LAW (TITLE 17 UNITED STATES CODE). UNAUTHORIZED REPRODUCTION
// AND/OR SALE MAY RESULT IN IMPRISONMENT OF UP TO ONE YEAR AND FINES
// OF UP TO $100,000 (17 USC 506). COPYRIGHT INFRINGERS MAY ALSO
// BE SUBJECT TO CIVIL LIABILITY.
//
// THIS NOTICE AND THE ABOVE COPYRIGHT NOTICE MUST REMAIN IN ALL
// COPIES AND ANY DERIVED WORK.
//
// ALL OF THIS CODE IS ORIGINAL WORK BY THE COPYRIGHT HOLDER.
//
// THIS DOCUMENT AND THE INFORMATION CONTAINED HEREIN IS
// PROVIDED ON AN "AS IS" BASIS AND DOUGLAS MARK ROYER
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED
// WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//
#include <SaS/String/String.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			std::map<const char *,
			    Locale::CharMap *,
			    CStringCompareOperator>	Locale::CharMap::_MapBySymbolicName;

			std::multimap<const char *,
			    Locale::CharMap *,
			    CStringCompareOperator>	Locale::CharMap::_MapByCodeSetName;

			Locale::CharMap::CharMap()
			{
				CodeSetName = nullptr;
				SymbolicName = nullptr;
				Comment = nullptr;
				Octets = nullptr;
				CharMapID = 0;
				OctetsLen = 0;
				Width = 0;

				return;
			}

			Locale::CharMap::~CharMap()
			{
				if (getInstance() == 1) {
					if (CodeSetName != nullptr) {
						StringCache::Remove(CodeSetName);
						CodeSetName = nullptr;
					}

					if (SymbolicName != nullptr) {
						StringCache::Remove(SymbolicName);
						SymbolicName = nullptr;
					}

					if (Comment != nullptr) {
						StringCache::Remove(Comment);
						Comment = nullptr;
					}

					if (Octets != nullptr) {
						StringCache::Remove((const char *)Octets);
						Octets = nullptr;
					}

					CharMapID = 0;
					OctetsLen = 0;
					Width = 0;
				}

				return;
			}


			bool
			Locale::CharMap::Parse(const char * FileName)
			{
				bool			Results = false;

				if (FileName != nullptr) {
					File	*	Fp = new File();

					if (Fp->Open(FileName, O_RDONLY)) {
						const char * Delim0 = "><";
						const char * Delim = " \t\n";
						char		Delim2[5];
						char	*	SavePtr0 = nullptr;
						char	*	SavePtr = nullptr;
						char	*	SavePtr2 = nullptr;
						char	*	Buffer = new char[1024];
						char	*	Ptr0 = nullptr;
						char	*	Ptr = nullptr;
						char	*	Ptr2 = nullptr;
						char	*	Range2 = nullptr;
						uint64_t	Length = sizeof(Buffer);
						char			CommentCharacter = '#';
						char			EscapeCharacter = '\\';
						uint8_t		Min = 1;
						uint8_t		Max = 1;
						uint8_t		Width = 1;
						uint8_t		DefaultWidth = 1;
						CharMap	*	Map = nullptr;
						bool			CharMapMode = false;
						bool			WidthMode = false;
						bool			Range = false;

						// Read one line at a time.
						//
						while (Fp->ReadLine((uint8_t **)&Buffer, Length)) {

							Ptr = strtok_r(Buffer, Delim, &SavePtr);

							if (Ptr == nullptr) {
								continue;
							}

							if (strcmp(Ptr, "<code_set_name>") == 0) {
								Ptr = strtok_r(nullptr, Delim, &SavePtr);

								if (Ptr != nullptr) {
									Map = new CharMap();
									Map->CodeSetName = StringCache::Add(Ptr);
								}

							} else if (strcmp(Ptr, "<comment_char>") == 0) {
								Ptr = strtok_r(nullptr, Delim, &SavePtr);

								if (Ptr != nullptr) {
									CommentCharacter = *Ptr;
								}

							} else if (strcmp(Ptr, "<escape_char>") == 0) {
								Ptr = strtok_r(nullptr, Delim, &SavePtr);

								if (Ptr != nullptr) {
									EscapeCharacter = *Ptr;
									Delim2[0] = EscapeCharacter;
									Delim2[1] = ' ';
									Delim2[2] = '\t';
									Delim2[3] = 0;
								}

							} else if (strcmp(Ptr, "<mb_cur_min>") == 0) {
								Ptr = strtok_r(nullptr, Delim, &SavePtr);

								if (Ptr != nullptr) {
									Min = atoi(Ptr);
								}

							} else if (strcmp(Ptr, "<mb_cur_max>") == 0) {
								Ptr = strtok_r(nullptr, Delim, &SavePtr);

								if (Ptr != nullptr) {
									Max = atoi(Ptr);
								}

							} else if (strcmp(Ptr, "DEFAULT_WIDTH") == 0) {
								Ptr = strtok_r(nullptr, Delim, &SavePtr);

								if (Ptr != nullptr) {
									DefaultWidth = atoi(Ptr);
								}

							} else if (strcmp(Ptr, "CHARMAP") == 0) {
								CharMapMode = true;

							} else if (strcmp(Ptr, "WIDTH") == 0) {
								WidthMode = true;

							} else if (strcmp(Ptr, "END CHARMAP") == 0) {
								CharMapMode = false;

							} else if (strcmp(Ptr, "END WIDTH") == 0) {
								WidthMode = false;

							} else if (Buffer[0] == '<') {

								if (CharMapMode) {
									// <SYMBOL> octets OPTIONAL-COMMENT
									// or
									// <SYMBOL>...<SYMBOL2> octets-start OPTIONAL-COMMENT
									//
									// https://pubs.opengroup.org/onlinepubs/7908799/xbd/charset.html
									// Says that the number part of the symbolic name is one
									// more each time. The example does not show hex, the
									// files contain hex. What a weak spec. I assume hex.
									//
									Ptr = strtok_r(nullptr, Delim0, &SavePtr);

									if (Ptr != nullptr) {
										Map->SymbolicName = StringCache::Add(Ptr);
										Ptr = strtok_r(nullptr, Delim0, &SavePtr);

										if (Ptr != nullptr) {
											//
											if (strcmp(Ptr, "...") == 0) {
												Range = true;

												if ((Ptr0 = strtok_r(&Ptr[3], Delim0, &SavePtr0)) != nullptr) {
													Range2 = strdup(Ptr0);
												}

											} else {
												Range = false;
											}
										}

										Ptr = strtok_r(nullptr, Delim, &SavePtr);

										if (Ptr != nullptr) {
											size_t			OctetOffset = 0;
											char				Buffer2[10];
											unsigned int	iTmp = 0;

											while ((Ptr2 = strtok_r(Ptr, Delim2, &SavePtr2)) != nullptr) {
												if (Ptr2 != nullptr) {
													if (Ptr2[0] == 'x') {
														sscanf(Ptr2, "%x", &iTmp);
														Buffer2[OctetOffset] = (char)iTmp;

													} else if (Ptr2[0] == 'd') {
														sscanf(Ptr2, "%u", &iTmp);
														Buffer2[OctetOffset] = (char)iTmp;

													} else if (Ptr[0] == 'o') {
														sscanf(Ptr2, "%o", &iTmp);
														Buffer2[OctetOffset] = (char)iTmp;

													} else {
														// No clue - error.
														break;
													}

													Map->Octets = StringCache::Add(Buffer2);
													Map->OctetsLen = strlen(Map->Octets);
													OctetOffset++;
												}
											}

											// Optional comment.
											//
											Ptr = strtok_r(nullptr, "\n", &SavePtr);

											if (Ptr != nullptr) {
												if (strlen(Ptr) > 0) {
													Map->Comment = StringCache::Add(Ptr);
												}
											}
										}
									}

								} else if (WidthMode) {

								}
							} else {
								/*EMPTY*/
								// Ignore whatever else lines.
							}
						}
					}
				}

				return (Results);
			}

		}
	}
}
