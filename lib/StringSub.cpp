//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2019 Software and Services LLC, All Rights Reserved.
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
// THIS	DOCUMENT AND THE INFORMATION CONTAINED HEREIN IS
// PROVIDED ON AN "AS IS" BASIS AND Software and Services LLC.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED,	INCLUDING BUT
// NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED WARRANTIES
// OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// THIS SOURCE CODE IS UNPUBLISHED WORK FULLY PROTECTED BY THE UNITED
// STATES COPYRIGHT LAWS AND IS CONSIDERED A TRADE SECRET BELONGING
// TO THE COPYRIGHT HOLDER.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//

#include <SaS/String/CopyRightNotice.h>
#include <SaS/String/String.hpp>
#include <SaS/String/ROString.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			ROString	*
			String::SubROString(size_t Offset, size_t Count) const
			{
				ROString	*	Results = nullptr;

				if (Count == 0) {
					Count = Length();
				}

				if (Offset < Length()) {

					const_iterator	it = cbegin();

					it = it[Offset];

					CharacterUnitWidth_e	Width;

					if (IsReadOnly()) {
						Width = _RO->Width;

					} else {
						Width = _InputWidth;
					}

					switch (Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								const_iterator		BeginIt = cbegin();
								const char	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.str8();

									// Get Count characters.
									//
									const_iterator		EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new ROString(BeginPtr, Len);
								}
							}
							break;

						case Is16Bit_t: {
								const_iterator		BeginIt = cbegin();
								const char16_t	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.str16();

									// Get Count characters.
									//
									const_iterator	EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new ROString(BeginPtr, Len);
								}
							}
							break;

						case Is32Bit_t: {
								const_iterator		BeginIt = cbegin();
								const char32_t	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.str32();

									// Get Count characters.
									//
									const_iterator	EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new ROString(BeginPtr, Len);
								}
							}
							break;

						case IsWBit_t: {
								const_iterator		BeginIt = cbegin();
								const wchar_t	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.strW();

									// Get Count characters.
									//
									const_iterator	EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new ROString(BeginPtr, Len);
								}
							}
							break;

					}
				}

				return (Results);
			}

			String	*
			String::SubString(size_t Offset, size_t Count) const
			{
				String	*	Results = nullptr;

				if (Count == 0) {
					Count = Length();
				}

				if (Offset < Length()) {

					CharacterUnitWidth_e	Width;

					if (IsReadOnly()) {
						Width = _RO->Width;

					} else {
						Width = _InputWidth;
					}

					switch (Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								const_iterator		BeginIt = cbegin();
								const char	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.str8();

									// Get Count characters.
									//
									const_iterator	EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new ROString(BeginPtr, Len);
								}
							}
							break;

						case Is16Bit_t: {
								const_iterator		BeginIt = cbegin();
								const char16_t	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.str16();

									// Get Count characters.
									//
									const_iterator	EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new String();
									Results->Append(BeginPtr, Len);
								}
							}
							break;

						case Is32Bit_t: {
								const_iterator		BeginIt = cbegin();
								const char32_t	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.str32();

									// Get Count characters.
									//
									const_iterator	EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new String();
									Results->Append(BeginPtr, Len);
								}
							}
							break;

						case IsWBit_t: {
								const_iterator		BeginIt = cbegin();
								const wchar_t	*	BeginPtr = nullptr;
								size_t			Len = 0;

								std::advance(BeginIt, Offset);

								if (BeginIt != cend()) {
									BeginPtr = BeginIt.strW();

									// Get Count characters.
									//
									const_iterator	EndIt = BeginIt;

									std::advance(EndIt, Count);

									// May be less than Count, when it exceeds
									// the length to the end of (*this).
									//
									Len = std::distance(BeginIt, EndIt);
									Results = new String();
									Results->Append(BeginPtr, Len);
								}
							}
							break;

					}
				}

				return (Results);
			}

		}
	}
}
