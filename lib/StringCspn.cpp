//
// BEGIN_DOUGLAS_MARK_ROYER_COPYRIGHT
//
// Copyright (C) 2017-2019 Douglas Mark Royer, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO DOUGLAS MARK ROYER. THIS CODE IS CONSIDERED
// A TRADE SECRET AND IS NOT TO BE DIVULGED OR USED BY PARTIES WHO HAVE
// NOT RECEIVED WRITTEN AUTHORIZATION FROM THE OWNER.
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
// END_DOUGLAS_MARK_ROYER_COPYRIGHT
//
#include <SaS/String/StringCache.hpp>
#include <sys/param.h>
#include <algorithm>
#include <ostream>

#include <unistr.h>
#include <unitypes.h>

#include <iconv.h>
#include <SaS/String/ROString.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			size_t
			String::strcspn(const_iterator & It, const String & Reject)
			{
				size_t		Results =  0;

				switch (It.Width()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strcspn(It.str8(), Reject.Get8());
						break;

					case Is16Bit_t:
						Results = strcspn(It.str16(), Reject.Get16());
						break;

					case Is32Bit_t:
						Results = strcspn(It.str32(), Reject.Get32());
						break;

					case IsWBit_t:
						Results = strcspn(It.strW(), Reject.GetW());
						break;

				}

				return (Results);
			}

			size_t
			String::strcspn(const_iterator & It,
			                const ROString & Reject)
			{
				size_t		Results =  0;

				size_t		Len = 0;

				switch (It.Width()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strcspn(It.str8(), Reject.Get8(Len));
						break;

					case Is16Bit_t:
						Results = strcspn(It.str16(), Reject.Get16(Len));
						break;

					case Is32Bit_t:
						Results = strcspn(It.str32(), Reject.Get32(Len));
						break;

					case IsWBit_t:
						Results = strcspn(It.strW(), Reject.GetW(Len));
						break;
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                const ROString & Reject)
			{
				return (strcspn(InStr, InStr.Length(), Reject,
				                Reject.Length()));
			}

			size_t
			String::strcspn(const ROString & InStr,
			                size_t InLen,
			                const ROString & Reject,
			                size_t RLen)
			{
				size_t			Results = 0;

				// Always convert Reject to InStr charset, as we need the
				// units into InStr and not into an InStr equivalent.
				//
				size_t			Len = InLen;

				if (Len == 0) {
					Len = InStr.Length();
				}

				const ROString	*	InDup = &InStr;
				const ROString	*	RejectDup = &Reject;

				if (Len != InLen) {
					InDup = new ROString(InStr, Len);
				}

				Len = RLen;

				if (Len == 0) {
					Len = Reject.Length();
				}

				if (Len != InLen) {
					RejectDup = new ROString(Reject, Len);
				}

				const String		*	NewReject = &Reject;

				if (strcmp(InStr._InputCharset,
				           Reject._InputCharset) != 0) {
					NewReject = InDup->ToCharset(RejectDup->_InputCharset,
					                             RejectDup->_InputWidth);

					if (RejectDup != &Reject) {
						delete RejectDup;
						RejectDup = nullptr;
					}
				}

				if (NewReject != nullptr) {
					// Both InStr and Reject are in the same charset.
					//
					size_t		iLen = 0;

					switch (InStr._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strcspn(InDup->Get8(iLen), RejectDup->Get8(iLen));
							break;

						case Is16Bit_t:
							Results = strcspn(InDup->Get16(iLen),
							                  RejectDup->Get16(iLen));
							break;

						case Is32Bit_t:
							Results = strcspn(InDup->Get32(iLen),
							                  RejectDup->Get32(iLen));
							break;

						case IsWBit_t:
							Results = strcspn(InDup->GetW(iLen), RejectDup->GetW(iLen));
							break;
					}

					if (InDup != &InStr) {
						delete InDup;
					}

					delete NewReject;
				}

				return (Results);
			}

			size_t
			String::strcspn(const_iterator & StartIt,
			                const char * const Reject)
			{
				size_t				Results = 0;

				switch (StartIt.Width()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strcspn(StartIt.str8(), Reject);
						break;

					case Is16Bit_t:
						Results = strcspn(StartIt.str16(), Reject);
						break;

					case Is32Bit_t:
						Results = strcspn(StartIt.str32(), Reject);
						break;

					case IsWBit_t:
						Results = strcspn(StartIt.strW(), Reject);
						break;
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                const char * const Reject)
			{
				size_t		Results = 0;

				switch (InStr._RO->Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t: {
							char	*	Out = nullptr;

							if (Charset8To8(nullptr,
							                Reject,
							                InStr._InputCharset,
							                Out)) {
								Results = strcspn(InStr._RO->Str.RO8, Out);
								delete  Out;
							}
						}
						break;

					case Is16Bit_t: {
							char16_t	*	Out = nullptr;

							if (Charset8To16(nullptr,
							                 Reject,
							                 InStr._InputCharset,
							                 Out)) {
								Results = strcspn(InStr._RO->Str.RO16, Out);
								delete  Out;
							}
						}
						break;

					case Is32Bit_t: {
							char32_t	*	Out = nullptr;

							if (Charset8To32(nullptr,
							                 Reject,
							                 InStr._InputCharset,
							                 Out)) {
								Results = strcspn(InStr._RO->Str.RO32, Out);
								delete  Out;
							}
						}
						break;

					case IsWBit_t: {
							wchar_t	*	Out = nullptr;

							if (Charset8ToW(nullptr,
							                Reject,
							                InStr._InputCharset,
							                Out)) {
								Results = strcspn(InStr._RO->Str.ROW, Out);
								delete  Out;
							}
						}
						break;
				}

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const ROString & Reject)
			{
				size_t		Results = 0;

				ROString	NewIn(InStr);
				String	*	NewReject = Reject.ToCharset(InStr._InputCharset,
				                        InStr._InputWidth);

				if (NewReject != nullptr) {
					Results = strcspn(NewIn, *NewReject);
					delete NewReject;
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                const String & Reject)
			{
				size_t		Results = 0;

				if (Reject.IsReadOnly()) {
					Results = strcspn(InStr, (ROString &)Reject);

				} else {

					// Not really needed here, but the method uses one.
					//
					String::const_iterator	InIt = InStr.cbegin();
					String					*				RejectInDestCs = nullptr;

					RejectInDestCs = Reject.ToCharset(InStr._InputCharset,
					                                  InStr._InputWidth);

					if (RejectInDestCs != nullptr) {
						switch (InStr._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = strcspn(InStr, InIt, RejectInDestCs->Get8());
								break;

							case Is16Bit_t:
								Results = strcspn(InStr, InIt, RejectInDestCs->Get16());
								break;

							case Is32Bit_t:
								Results = strcspn(InStr, InIt, RejectInDestCs->Get32());
								break;

							case IsWBit_t:
								Results = strcspn(InStr, InIt, RejectInDestCs->GetW());
								break;
						}

						delete RejectInDestCs;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const String & Reject)
			{
				size_t		Results = 0;

				if (InStr.IsReadOnly() && Reject.IsReadOnly()) {
					Results = strcspn((ROString &)InStr, (ROString &)Reject);

				} else if (InStr.IsReadOnly() && !Reject.IsReadOnly()) {
					Results = strcspn((ROString &)InStr, Reject);

				} else if (!InStr.IsReadOnly() && Reject.IsReadOnly()) {
					Results = strcspn(InStr, (ROString &)Reject);

				} else {
					switch (InStr._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strcspn(InStr.Get8(), Reject.Get8());
							break;

						case Is16Bit_t:
							Results = strcspn(InStr.Get16(), Reject.Get16());
							break;

						case Is32Bit_t:
							Results = strcspn(InStr.Get32(), Reject.Get32());
							break;

						case IsWBit_t:
							Results = strcspn(InStr.GetW(), Reject.GetW());
							break;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const char * const Reject)
			{
				size_t			Results = 0;

				if (Reject != nullptr) {
					CharacterUnitWidth_e	InWidth;

					if (InStr.IsReadOnly()) {
						InWidth = InStr._RO->Width;

					} else {
						InWidth = InStr._InputWidth;
					}

					switch (InWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char		*	RStr = nullptr;

								if (Charset8To8(nullptr,
								                Reject,
								                InStr._InputCharset,
								                RStr)) {

									const char	 *	RPtr = RStr;
									ssize_t			InLen = InStr.Length();
									ssize_t			InCLen = 0;
									ssize_t			RCLen = 0;
									bool			Done = false;

									const_iterator		InIt = InStr.cbegin();

									while (InIt != InStr.cend() && !Done) {
										if (std::distance(InStr.cend(), InIt) < InCLen) {
											// At end of available data.
											//
											Done = true;
											break;
										}

										RPtr = RStr;
										InCLen = CharacterUnits(InIt.str8());
										RCLen = CharacterUnits(RPtr);

										while (*RPtr != 0) {
											if (InCLen != RCLen) {
												InIt++;
												RPtr += RCLen;
												RCLen = CharacterUnits(RPtr);
												continue;
											}

											if (memcmp(InIt.str8(), RPtr, InLen) == 0) {
												// Found reject, exit.
												//
												Done = true;
												break;
											}

											RPtr++;
										}

										if (!Done) {
											InIt++;
											Results++;
										}
									}

									delete RStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t		*	RStr = nullptr;

								if (Charset8To16(nullptr,
								                 Reject,
								                 InStr._InputCharset,
								                 RStr)) {

									const char16_t	 *	RPtr = RStr;
									ssize_t			InCLen = 0;
									ssize_t			RCLen = 0;
									bool			Done = false;

									const_iterator		InIt = InStr.cbegin();

									while (InIt != InStr.cend() && !Done) {
										if (std::distance(InStr.cend(), InIt) < InCLen) {
											// At end of available data.
											//
											Done = true;
											break;
										}

										RPtr = RStr;
										InCLen = CharacterUnits(InIt.str16());
										RCLen = CharacterUnits(RPtr);

										while (*RPtr != 0) {
											if (InCLen != RCLen) {
												InIt++;
												RPtr += RCLen;
												RCLen = CharacterUnits(RPtr);
												continue;
											}

											if (memcmp(InIt.str16(), RPtr, InCLen) == 0) {
												// Found reject, exit.
												//
												Done = true;
												break;
											}

											RPtr++;
										}

										if (!Done) {
											InIt++;
											Results++;
										}
									}

									delete RStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t		*	RStr = nullptr;

								if (Charset8To32(nullptr,
								                 Reject,
								                 InStr._InputCharset,
								                 RStr)) {

									const char32_t	 *	RPtr = RStr;
									ssize_t			InCLen = 0;
									ssize_t			RCLen = 0;
									bool			Done = false;

									const_iterator		InIt = InStr.cbegin();

									while (InIt != InStr.cend() && !Done) {
										if (std::distance(InStr.cend(), InIt) < InCLen) {
											// At end of available data.
											//
											Done = true;
											break;
										}

										RPtr = RStr;
										InCLen = CharacterUnits(InIt.str32());
										RCLen = CharacterUnits(RPtr);

										while (*RPtr != 0) {
											if (InCLen != RCLen) {
												InIt++;
												RPtr += RCLen;
												RCLen = CharacterUnits(RPtr);
												continue;
											}

											if (memcmp(InIt.str32(), RPtr, InCLen) == 0) {
												// Found reject, exit.
												//
												Done = true;
												break;
											}

											RPtr++;
										}

										if (!Done) {
											InIt++;
											Results++;
										}
									}

									delete RStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t		*	RStr = nullptr;

								if (Charset8ToW(nullptr,
								                Reject,
								                InStr._InputCharset,
								                RStr)) {

									const wchar_t	 *	RPtr = RStr;
									ssize_t			InCLen = 0;
									ssize_t			RCLen = 0;
									bool			Done = false;

									const_iterator		InIt = InStr.cbegin();

									while (InIt != InStr.cend() && !Done) {
										if (std::distance(InStr.cend(), InIt) < InCLen) {
											// At end of available data.
											//
											Done = true;
											break;
										}

										RPtr = RStr;
										InCLen = CharacterUnits(InIt.strW());
										RCLen = CharacterUnits(RPtr);

										while (*RPtr != 0) {
											if (InCLen != RCLen) {
												InIt++;
												RPtr += RCLen;
												RCLen = CharacterUnits(RPtr);
												continue;
											}

											if (memcmp(InIt.strW(), RPtr, InCLen) == 0) {
												// Found reject, exit.
												//
												Done = true;
												break;
											}

											RPtr++;
										}

										if (!Done) {
											InIt++;
											Results++;
										}
									}

									delete RStr;
								}
							}
							break;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const char16_t * const Reject)
			{
				size_t			Results = 0;

				if (InStr.IsReadOnly()) {
					/**@todo*/

				} else {
					if (Reject != nullptr) {
						if (strcmp(InStr._InputCharset, Current16BitCharset) == 0) {
							Results = strcspn(InStr.Get16(), Reject);

						} else {
							String		RCopy(Reject);
							String	*	CS = RCopy.ToCharset(InStr._InputCharset,
							                                 InStr._InputWidth);

							Results = strcspn(InStr, *CS);
							delete CS;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const char32_t * const Reject)
			{
				size_t			Results = 0;

				if (InStr.IsReadOnly()) {
					/**@todo*/

				} else {
					if (Reject != nullptr) {
						if (strcmp(InStr._InputCharset, Current32BitCharset) == 0) {
							Results = strcspn(InStr.Get32(), Reject);

						} else {
							String		RCopy(Reject);
							String	*	CS = RCopy.ToCharset(InStr._InputCharset,
							                                 InStr._InputWidth);

							Results = strcspn(InStr, *CS);
							delete CS;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const wchar_t * const Reject)
			{
				size_t			Results = 0;

				if (InStr.IsReadOnly()) {
					/**@todo*/

				} else {
					if (Reject != nullptr) {
						if (strcmp(InStr._InputCharset, CurrentWBitCharset) == 0) {
							Results = strcspn(InStr.GetW(), Reject);

						} else {
							String		RCopy(Reject);
							String	*	CS = RCopy.ToCharset(InStr._InputCharset,
							                                 InStr._InputWidth);

							Results = strcspn(InStr, *CS);
							delete CS;

						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const std::string & Reject)
			{
				size_t			Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const std::u16string & Reject)
			{
				size_t			Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const std::u32string & Reject)
			{
				size_t			Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const String & InStr,
			                const std::wstring & Reject)
			{
				size_t			Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const char * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					Results = strcspn(InStr, strlen(InStr),
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                size_t InLen,
			                const char * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {

					if (InLen == 0) {
						InLen = strlen(InStr);
					}

					if (RejectLen == 0) {
						RejectLen = strlen(Reject);
					}

					const char  *	InPtr = InStr;
					const char  *	RPtr = Reject;
					size_t	InToGo = InLen;
					size_t	RToGo = RejectLen;
					size_t	InCLen = InLen;
					size_t	RCLen = RejectLen;

					while (*InPtr != 0 && InToGo > 0 && !Done) {
						RPtr = Reject;
						RToGo = RejectLen;
						InCLen = CharacterUnits(InPtr);
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								InPtr += InCLen;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(InPtr, RPtr, InCLen) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const char16_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char	*	Out = nullptr;

					if (String::Charset16To8(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const char32_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char	*	Out = nullptr;

					if (String::Charset32To8(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char	*	Out = nullptr;

					if (String::CharsetWTo8(nullptr,
					                        Reject,
					                        nullptr,
					                        Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const String & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.Get8());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const std::string & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const std::u16string & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const std::u32string & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char * const InStr,
			                const std::wstring & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const char * const Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset8To16(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const char16_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					Results = strcspn(InStr, strlen(InStr),
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                size_t InLen,
			                const char16_t * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {

					if (InLen == 0) {
						InLen = strlen(InStr);
					}

					if (RejectLen == 0) {
						RejectLen = strlen(Reject);
					}

					const char16_t  *	InPtr = InStr;
					const char16_t  *	RPtr = Reject;
					size_t		InCLen = 0;
					size_t		RCLen = 0;
					size_t		InToGo = InLen;
					size_t		RToGo = RejectLen;

					while (*InPtr != 0 && InToGo > 0 && !Done) {
						RPtr = Reject;
						RToGo = RejectLen;
						InCLen = CharacterUnits(InPtr);
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								InPtr += InCLen;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(InPtr, RPtr, InCLen * sizeof(char16_t)) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const char32_t * const Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset32To16(nullptr,
					                          Reject,
					                          nullptr,
					                          Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const std::string & Reject)
			{
				return (strcspn(InStr, Reject.c_str()));
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const std::u16string & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const std::u32string & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char16_t * const InStr,
			                const std::wstring & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strcspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const char * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset8To32(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const char16_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset16To32(nullptr,
					                          Reject,
					                          nullptr,
					                          Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const char32_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					Results = strcspn(InStr, strlen(InStr),
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                size_t InLen,
			                const char32_t * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {
					if (InLen == 0) {
						InLen = strlen(InStr);
					}

					if (RejectLen == 0) {
						RejectLen = strlen(Reject);
					}

					const char32_t  *	InPtr = InStr;
					const char32_t  *	RPtr = Reject;
					size_t		InToGo = InLen;
					size_t		RToGo = RejectLen;
					size_t		InCLen = 0;
					size_t		RCLen = 0;

					while (*InPtr != 0 && InToGo > 0 && !Done) {
						RPtr = Reject;
						RToGo = RejectLen;
						InCLen = CharacterUnits(InPtr);
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								InPtr += InCLen;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(InPtr, RPtr, InCLen * sizeof(char32_t)) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::CharsetWTo32(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strcspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const std::string & Reject)
			{
				size_t		Results = 0;

				Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const std::u16string & Reject)
			{
				size_t		Results = 0;

				Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const std::u32string & Reject)
			{
				size_t		Results = 0;

				Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const std::wstring & Reject)
			{
				size_t		Results = 0;

				Results = strcspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strcspn(const char32_t * const InStr,
			                const String & Reject)
			{
				size_t		Results = strcspn(InStr, Reject.Get32());

				return (Results);
			}

			size_t
			String::strcspn(const wchar_t * const InStr,
			                const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					Results = strcspn(InStr, strlen(InStr),
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const wchar_t * const InStr,
			                const char * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					wchar_t		*		RejectInW = nullptr;

					if (String::Charset8ToW(nullptr,
					                        Reject,
					                        nullptr,
					                        RejectInW)) {

						Results = strcspn(InStr, strlen(InStr),
						                  RejectInW, strlen(RejectInW));
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const wchar_t * const InStr,
			                size_t InLen,
			                const wchar_t * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {
					if (InLen == 0) {
						InLen = strlen(InStr);
					}

					if (RejectLen == 0) {
						RejectLen = strlen(Reject);
					}

					const wchar_t  *	InPtr = InStr;
					const wchar_t  *	RPtr = Reject;
					size_t		InCLen = 0;
					size_t		RCLen = 0;
					size_t		InToGo = InLen;
					size_t		RToGo = RejectLen;

					if (InCLen == 0) {
						InCLen = strlen(InStr);
					}

					if (RCLen == 0) {
						RCLen = strlen(Reject);
					}

					while (*InPtr != 0 && InToGo > 0 && !Done) {
						RPtr = Reject;
						RToGo = RejectLen;
						InCLen = CharacterUnits(InPtr);
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								InPtr += InCLen;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(InPtr, RPtr, InCLen * sizeof(wchar_t)) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                String::const_iterator & it,
			                const char * const Reject)
			{
				size_t		Results = 0;

				if (Reject != nullptr) {
					Results = strcspn(InStr, InStr.Length(),
					                  it,
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                size_t InLen,
			                String::const_iterator & it,
			                const char * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				size_t		InToGo = InLen;
				size_t		RToGo = RejectLen;
				bool		Done = false;

				if (it != InStr.cend() && Reject != nullptr) {
					const char  *	RPtr = Reject;
					size_t	InCLen = 0;
					size_t	RCLen = 0;

					if (InCLen == 0) {
						InCLen = InStr.Length();
					}

					if (RCLen == 0) {
						RCLen = strlen(Reject);
					}

					while (it != InStr.cend() && InToGo > 0 && !Done) {
						RToGo = RejectLen;
						InCLen = CharacterUnits(it.str8());
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								it++;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(it.str8(), RPtr, InCLen) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							it++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                String::const_iterator & it,
			                const char16_t * const Reject)
			{
				size_t		Results = 0;

				if (Reject != nullptr) {
					Results = strcspn(InStr, InStr.Length(),
					                  it,
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                size_t InLen,
			                String::const_iterator & it,
			                const char16_t * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				size_t		InToGo = InLen;
				size_t		RToGo = RejectLen;
				bool		Done = false;

				if (it != InStr.cend() && Reject != nullptr) {
					const char16_t  *	RPtr = Reject;
					size_t		InCLen = 0;
					size_t		RCLen = 0;

					if (InCLen == 0) {
						InCLen = InStr.Length();
					}

					if (RCLen == 0) {
						RCLen = strlen(Reject);
					}

					while (it != InStr.cend() && InToGo > 0 && !Done) {
						RToGo = RejectLen;
						InCLen = CharacterUnits(it.str8());
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								it++;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(it.str16(), RPtr, InCLen) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							it++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                String::const_iterator & it,
			                const char32_t * const Reject)
			{
				size_t		Results = 0;

				if (Reject != nullptr) {
					Results = strcspn(InStr, InStr.Length(),
					                  it,
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                size_t InLen,
			                String::const_iterator & it,
			                const char32_t * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				size_t		InToGo = InLen;
				size_t		RToGo = RejectLen;
				bool		Done = false;

				if (it != InStr.cend() && Reject != nullptr) {
					const char32_t  *	RPtr = Reject;
					size_t		InCLen = 0;
					size_t		RCLen = 0;

					if (InCLen == 0) {
						InCLen = InStr.Length();
					}

					if (RCLen == 0) {
						RCLen = strlen(Reject);
					}

					while (it != InStr.cend() && InToGo > 0 && !Done) {
						RToGo = RejectLen;
						InCLen = CharacterUnits(it.str8());
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								it++;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(it.str32(), RPtr, InCLen) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							it++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                String::const_iterator & it,
			                const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (Reject != nullptr) {
					Results = strcspn(InStr, InStr.Length(),
					                  it,
					                  Reject, strlen(Reject));
				}

				return (Results);
			}

			size_t
			String::strcspn(const ROString & InStr,
			                size_t InLen,
			                String::const_iterator & it,
			                const wchar_t * const Reject,
			                size_t RejectLen)
			{
				size_t		Results = 0;

				size_t		InToGo = InLen;
				size_t		RToGo = RejectLen;
				bool		Done = false;

				if (it != InStr.cend() && Reject != nullptr) {
					const wchar_t  *	RPtr = Reject;
					size_t		InCLen = 0;
					size_t		RCLen = 0;

					if (InCLen == 0) {
						InCLen = InStr.Length();
					}

					if (RCLen == 0) {
						RCLen = strlen(Reject);
					}

					while (it != InStr.cend() && InToGo > 0 && !Done) {
						RToGo = RejectLen;
						InCLen = CharacterUnits(it.str8());
						RCLen = CharacterUnits(RPtr);

						while (*RPtr != 0 && RToGo > 0) {
							// No point in comparing if the single character
							// we are looking at are different lengths.
							//
							if (InCLen != RCLen) {
								it++;
								RPtr += RCLen;
								InToGo--;
								RToGo--;
								RCLen = CharacterUnits(RPtr);
								continue;
							}

							if (InToGo >= RCLen) {
								if (memcmp(it.strW(), RPtr, InCLen) == 0) {
									Done = true;
									break;
								}
							}

							RPtr++;
						}

						if (!Done) {
							it++;
							Results++;
						}
					}
				}

				return (Results);
			}

		}
	}
}
