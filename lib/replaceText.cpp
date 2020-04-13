//
// BEGIN_COPYRIGHT
//
// Copyright (C) 2010-2015,2019 Software and Services LLC, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO Software and Services LLC.
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
// THIS  DOCUMENT  AND  THE  INFORMATION  CONTAINED  HEREIN  IS
// PROVIDED  ON  AN "AS IS" BASIS AND Software and Services LLC.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED,  INCLUDING  BUT
// NOT  LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN  WILL  NOT  INFRINGE  ANY  RIGHTS  OR   ANY   IMPLIED
// WARRANTIES  OF  MERCHANTABILITY  OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// THIS SOURCE CODE IS UNPUBLISHED WORK FULLY PROTECTED BY THE UNITED
// STATES COPYRIGHT LAWS AND IS CONSIDERED A TRADE SECRET BELONGING
// TO THE COPYRIGHT HOLDER.
//
// END_COPYRIGHT
//

#include <SaS/String/StringCache.hpp>
#include <string.h>
#include <SaS/String/replaceText.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

#ifdef FOO
			char	*
			replaceText(const char * id,
			            const char * oldText,
			            const char * newText)
			{
				char	*	results = nullptr;

				char	*	foundOld = (char *)strstr(id, oldText);

				if (foundOld == nullptr) {
					results = strdup(id);

				} else {
					if (strlen(oldText) == strlen(newText)) {

						results = strdup(id);

						while ((foundOld = (char *)strstr(results,
						                                  oldText)) != nullptr) {

							const char	*	Nptr = newText;
							size_t			len = strlen(newText);

							while (len > 0) {
								*foundOld = *Nptr;
								len--;
								foundOld++;
								Nptr++;
							}
						}

					} else {
						const size_t		oldLen = strlen(oldText);
						const size_t		newLen = strlen(newText);

						if (newLen < oldLen) {
							// newLen is shorter then oldLen.
							//
							size_t			diff = oldLen - newLen;

							results = strdup(id);

							while ((foundOld = (char *)strstr(results,
							                                  oldText)) != nullptr) {

								size_t			nLen = newLen;
								const char	*	Nptr = newText;

								while (nLen > 0) {
									*foundOld = *Nptr;
									nLen--;
									foundOld++;
									Nptr++;

									// Now move down the diff.
									//
									memmove(foundOld, foundOld + diff, strlen(foundOld) - diff);
									foundOld[strlen(foundOld) - diff] = '\0';
								}
							}

						} else {
							// New text larger then old text.
							//
							// Count the number of times that newText is in OldText.
							//
							int			times = 0;
							const char	*	foundIt = id;

							while ((foundIt = (char *)strstr(foundIt,
							                                 oldText)) != nullptr) {
								foundIt++;
								times++;
							}

							if (times > 0) {
								// Make room for the new data.
								//
								char		*	tmp;
								size_t			nLen = newLen;
								const char	*	Nptr = newText;

								tmp = new char[strlen(id) * times * 2];
								memset(tmp, '\0', strlen(id) * times * 2);
								strcpy(tmp, id);

								// Copy over the data and replace.
								//
								foundOld = tmp;

								while ((foundOld = (char *)strstr(foundOld,
								                                  oldText)) != nullptr) {
									nLen = newLen;

									// Move the existing string to the right.
									//
									memmove(foundOld + newLen, foundOld + 1,
									        strlen(foundOld + 1) );

									while (nLen > 0) {
										*foundOld = *Nptr;
										nLen--;
										foundOld++;
										Nptr++;
									}

									results = tmp;
								}
							}
						}
					}
				}

				return (results);
			}
#endif // FOO


			replaceText::replaceText()
			{
				return;
			}


			replaceText::~replaceText()
			{
				return;
			}

			bool
			replaceText::replace(std::vector<set *> & ofSet,
			                     char ** result,
			                     const char * source)
			{
				bool			results = false;

				char		*	ResultString = nullptr;
				const size_t		sCount = ofSet.size();

				if (result != nullptr && source != nullptr) {

					*result = nullptr;

					if (sCount == 0) {
						results = true;
						*result = strdup(source);

					} else {

						size_t		SetOffset = 0;
						set		*	theSet = nullptr;
						size_t		Times = 0;
						size_t		SourceOffset = 0;
						size_t		LengthReplace = 0;
						size_t		LengthWith = 0;
						size_t		LengthSource = 0;

						for (SetOffset = 0; SetOffset < sCount; SetOffset++) {
							theSet = (set *)ofSet[static_cast<unsigned int>(SetOffset)];

							if (theSet != nullptr && theSet->replace != nullptr
							    && theSet->with != nullptr) {

								LengthReplace = strlen(theSet->replace);
								LengthWith = strlen(theSet->with);
								LengthSource = strlen(source);
								Times = 0;

								const char     *    found = nullptr;

								// Count the number of times the old string is in source.
								//
								// If the new string will be bigger, how much bigger?
								//
								for (SourceOffset = 0; SourceOffset < LengthSource; ) {
									if ((found = strstr(&source[SourceOffset],
									                    theSet->replace)) != nullptr) {
										Times++;
										SourceOffset = (found + LengthReplace) - source;
										continue;
									}

									SourceOffset++;
								}


								if (Times == 0) {

									ResultString = strdup(source);

									if (*result != nullptr) {
										delete *result;
									}

									*result = ResultString;
									source = ResultString;

								} else {

									// Make sure there is plenty of room.
									//
									size_t              DestOffset = 0;

									ResultString = new char[LengthSource + (LengthReplace *
									                                        Times) + 100];

									for (SourceOffset = 0; SourceOffset < LengthSource; ) {
										if (strncmp(theSet->replace, &source[SourceOffset],
										            LengthReplace) == 0) {
											strcat(ResultString, theSet->with);
											SourceOffset += LengthReplace;
											DestOffset += LengthWith;

										} else {
											ResultString[DestOffset++] = source[SourceOffset++];
											ResultString[DestOffset] = '\0';
										}
									}

									if (*result != nullptr) {
										delete *result;
									}

									*result = strdup(ResultString);
									source = *result;

									results = true;         // Something replaced.
								}
							}
						}
					}
				}

				return (results);
			}

		}
	}
}
