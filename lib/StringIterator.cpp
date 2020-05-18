//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2019-2020 Software and Services LLC, All Rights Reserved.
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

// Indicate to the library at compile time, that
// we do support multibyte characters.
//

#include <SaS/String/StringCache.hpp>
#include <SaS/String/ROString.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			/*
			 * ------------ String::iterator
			 */

			String::IteratorBase::IteratorBase()
			{
				memset(&_It, 0, sizeof(_It));
				_Direction = ItForward_t;
				_Segments = nullptr;
				_SegmentsOffset = 0;
				_AllocatedSegments = false;

				return;
			}

			String::IteratorBase::~IteratorBase()
			{
				_Direction = ItForward_t;
				_SegmentsOffset = 0;

				if (_Segments != nullptr) {
					if (_AllocatedSegments) {
						delete _Segments->at(0);
						delete _Segments;
						_AllocatedSegments = false;
					}

					_Segments = nullptr;
				}

				memset(&_It, 0, sizeof(_It));

				return;
			}

			String::iterator::iterator()
			{
				/*EMPTY*/
				return;
			}

			String::iterator::iterator(const iterator & From)
			{
				_Direction = From._Direction;
				_Segments = From._Segments;
				_SegmentsOffset = From._SegmentsOffset;

				StringSeg	*	Seg = _Segments->at(_SegmentsOffset);

				switch (Seg->Width) {

					case Is8Bit_t:
						_It.It8 = new iteratorType<char>();
						_It.It8->_First = From._It.It8->_First;
						_It.It8->_Ptr = From._It.It8->_Ptr;
						_It.It8->_Last = From._It.It8->_Last;
						break;

					case Is16Bit_t:
						_It.It16 = new iteratorType<char16_t>();
						_It.It16->_First = From._It.It16->_First;
						_It.It16->_Ptr = From._It.It16->_Ptr;
						_It.It16->_Last = From._It.It16->_Last;
						break;

					case Is32Bit_t:
						_It.It32 = new iteratorType<char32_t>();
						_It.It32->_First = From._It.It32->_First;
						_It.It32->_Ptr = From._It.It32->_Ptr;
						_It.It32->_Last = From._It.It32->_Last;
						break;

					case IsWBit_t:
						_It.ItW = new iteratorType<wchar_t>();
						_It.ItW->_First = From._It.ItW->_First;
						_It.ItW->_Ptr = From._It.ItW->_Ptr;
						_It.ItW->_Last = From._It.ItW->_Last;
						break;
				}

				return;
			}

			String::iterator::iterator(const char * Ptr, size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Ptr, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.It8 = new iteratorType<char>((const char *)Ptr, Len);

				return;
			}

			String::iterator::iterator(const char16_t * Ptr, size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Ptr, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.It16 = new iteratorType<char16_t>((const char16_t *)Ptr, Len);

				return;
			}

			String::iterator::iterator(const char32_t * Ptr, size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Ptr, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.It32 = new iteratorType<char32_t>((const char32_t *)Ptr, Len);

				return;
			}

			String::iterator::iterator(const wchar_t * Ptr, size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Ptr, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.ItW = new iteratorType<wchar_t>((const wchar_t *)Ptr, Len);

				return;
			}

			String::iterator::iterator(const char * Start,
			                           const char * Ptr,
			                           size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Start, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.It8 = new iteratorType<char>((const char *)Start,
				                                 Ptr,
				                                 Len);

				return;
			}

			String::iterator::iterator(const char16_t * Start,
			                           const char16_t * Ptr,
			                           size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Start, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.It16 = new iteratorType<char16_t>((const char16_t *)Start,
				                                      Ptr,
				                                      Len);

				return;
			}

			String::iterator::iterator(const char32_t * Start,
			                           const char32_t * Ptr,
			                           size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Start, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.It32 = new iteratorType<char32_t>((const char32_t *)Start,
				                                      Ptr,
				                                      Len);

				return;
			}

			String::iterator::iterator(const wchar_t * Start,
			                           const wchar_t * Ptr,
			                           size_t Len)
			{
				StringSeg	*	Seg = new StringSeg(Start, Len);

				_Direction = ItForward_t;
				_Segments = new std::vector<StringSeg *>();
				_Segments->push_back(Seg);
				_AllocatedSegments = true;
				_It.ItW = new iteratorType<wchar_t>((const wchar_t *)Start,
				                                    Ptr,
				                                    Len);

				return;
			}

			CharacterUnitWidth_e
			String::iterator::Width() const
			{
				return (_Segments->at(_SegmentsOffset)->Width);
			}

			String::iterator::self_type
			String::iterator::operator=(const self_type & From)
			{
				_Direction = From._Direction;
				_Segments = From._Segments;
				_SegmentsOffset = From._SegmentsOffset;

				StringSeg	*	Seg = _Segments->at(_SegmentsOffset);

				switch (Seg->Width) {

					case Is8Bit_t:
						_It.It8 = new iteratorType<char>();
						_It.It8->_First = From._It.It8->_First;
						_It.It8->_Ptr = From._It.It8->_Ptr;
						_It.It8->_Last = From._It.It8->_Last;
						break;

					case Is16Bit_t:
						_It.It16 = new iteratorType<char16_t>();
						_It.It16->_First = From._It.It16->_First;
						_It.It16->_Ptr = From._It.It16->_Ptr;
						_It.It16->_Last = From._It.It16->_Last;
						break;

					case Is32Bit_t:
						_It.It32 = new iteratorType<char32_t>();
						_It.It32->_First = From._It.It32->_First;
						_It.It32->_Ptr = From._It.It32->_Ptr;
						_It.It32->_Last = From._It.It32->_Last;
						break;

					case IsWBit_t:
						_It.ItW = new iteratorType<wchar_t>();
						_It.ItW->_First = From._It.ItW->_First;
						_It.ItW->_Ptr = From._It.ItW->_Ptr;
						_It.ItW->_Last = From._It.ItW->_Last;
						break;
				}

				return (*this);
			}

			void
			String::IteratorBase::_Inc(int64_t UnitCount)
			{
				StringSeg	*	Seg = _Segments->at(_SegmentsOffset);

				size_t			OneCharUnits = 0;
				size_t			ToGo = CharCount;
				size_t			InCurrent = 0;

				do {
					switch (Seg->Width) {

						case Is8Bit_t:

							OneCharUnits = strwidth(_It.It8->_Ptr, 1);

							// Two possibilities here (1) this segment contain the entire character,
							// (2) the single character is split across segments.
							//
							// (2) can happen with somone appends by character units,
							// and not characters. Hopefully the rest is not an
							// invalid character or missing.
							//
							if (_It.It8->_Ptr + OneCharUnits < _It.It8->_Last ) {
								// Fits.
								// Advanced 1 character that is OneCharUnits wide.
								//
								_It.It8->_Ptr += OneCharUnits;
								ToGo--;
								// Done
								//
								continue;

							} else if (_It.It8->_Ptr + OneCharUnits == _It.It8->_Last ) {
								ToGo--;

								if ((_SegmentsOffset + 1) < _Segments->size()) {
									_SegmentsOffset++;
									// Done
									//
									Seg = _Segments->at(_SegmentsOffset);
									_It.It8->_First = Seg->Str.s8;
									_It.It8->_Ptr = Seg->Str.s8;
									_It.It8->_Last = Seg->Str.s8 + Seg->StrUnits - 1;

								} else {
									_It.It8->_Ptr = _It.It8->_Last;
								}

								continue;

							} else {
								// Does not fit in this segment. Some of it
								// is in the next segment.
								//
								InCurrent = (_It.It8->_Last - _It.It8->_Ptr);

								if (OneCharUnits > InCurrent) {

									// Go to the next segment, if exists.
									//
									if ((_SegmentsOffset + 1) < _Segments->size()) {
										_SegmentsOffset++;
										Seg = _Segments->at(_SegmentsOffset);

										// Skip them
										//
										_It.It8->_First = Seg->Str.s8;
										_It.It8->_Ptr = Seg->Str.s8 + (OneCharUnits - InCurrent);
										_It.It8->_Last = Seg->Str.s8 + Seg->StrUnits - 1;

									} else {
										// No more segments.
										//
										_It.It8->_Ptr = _It.It8->_Last;

										// Nothing else to do, end loop.
										//
										continue;
									}

								} else {
									// It was all in this segment, move forward.
									//
									_It.It8->_Ptr += InCurrent;
								}
							}

							break;

						case Is16Bit_t:

							OneCharUnits = strwidth(_It.It16->_Ptr, 1);

							// Two possibilities here (1) this segment contain the entire character,
							// (2) the single character is split across segments.
							//
							// (2) can happen with somone appends by character units,
							// and not characters. Hopefully the rest is not an
							// invalid character or missing.
							//
							if (_It.It16->_Ptr + OneCharUnits < _It.It16->_Last ) {
								// Fits.
								// Advanced 1 character that is OneCharUnits wide.
								//
								_It.It16->_Ptr += OneCharUnits;
								ToGo--;
								// Done
								//
								continue;

							} else if (_It.It16->_Ptr + OneCharUnits == _It.It16->_Last ) {
								ToGo--;

								if ((_SegmentsOffset + 1) < _Segments->size()) {
									_SegmentsOffset++;
									// Done
									//
									Seg = _Segments->at(_SegmentsOffset);
									_It.It16->_First = Seg->Str.s16;
									_It.It16->_Ptr = Seg->Str.s16;
									_It.It16->_Last = Seg->Str.s16 + Seg->StrUnits - 1;

								} else {
									_It.It16->_Ptr = _It.It16->_Last;
								}

								continue;

							} else {
								// Does not fit in this segment. Some of it
								// is in the next segment.
								//
								InCurrent = (_It.It16->_Last - _It.It16->_Ptr);

								if (OneCharUnits > InCurrent) {

									// Go to the next segment, if exists.
									//
									if ((_SegmentsOffset + 1) < _Segments->size()) {
										_SegmentsOffset++;
										Seg = _Segments->at(_SegmentsOffset);

										// Skip them
										//
										_It.It16->_First = Seg->Str.s16;
										_It.It16->_Ptr = Seg->Str.s16 + (OneCharUnits - InCurrent);
										_It.It16->_Last = Seg->Str.s16 + Seg->StrUnits - 1;

									} else {
										// No more segments.
										//
										_It.It16->_Ptr = _It.It16->_Last;

										// Nothing else to do, end loop.
										//
										continue;
									}

								} else {
									// It was all in this segment, move forward.
									//
									_It.It16->_Ptr += InCurrent;
								}
							}

							break;

						case Is32Bit_t:

							OneCharUnits = strwidth(_It.It32->_Ptr, 1);

							// Two possibilities here (1) this segment contain the entire character,
							// (2) the single character is split across segments.
							//
							// (2) can happen with somone appends by character units,
							// and not characters. Hopefully the rest is not an
							// invalid character or missing.
							//
							if (_It.It32->_Ptr + OneCharUnits < _It.It32->_Last ) {
								// Fits.
								// Advanced 1 character that is OneCharUnits wide.
								//
								_It.It32->_Ptr += OneCharUnits;
								ToGo--;
								// Done
								//
								continue;

							} else if (_It.It32->_Ptr + OneCharUnits == _It.It32->_Last ) {
								ToGo--;

								if ((_SegmentsOffset + 1) < _Segments->size()) {
									_SegmentsOffset++;
									// Done
									//
									Seg = _Segments->at(_SegmentsOffset);
									_It.It32->_First = Seg->Str.s32;
									_It.It32->_Ptr = Seg->Str.s32;
									_It.It32->_Last = Seg->Str.s32 + Seg->StrUnits - 1;

								} else {
									_It.It32->_Ptr = _It.It32->_Last;
								}

								continue;

							} else {
								// Does not fit in this segment. Some of it
								// is in the next segment.
								//
								InCurrent = (_It.It32->_Last - _It.It32->_Ptr);

								if (OneCharUnits > InCurrent) {

									// Go to the next segment, if exists.
									//
									if ((_SegmentsOffset + 1) < _Segments->size()) {
										_SegmentsOffset++;
										Seg = _Segments->at(_SegmentsOffset);

										// Skip them
										//
										_It.It32->_First = Seg->Str.s32;
										_It.It32->_Ptr = Seg->Str.s32 + (OneCharUnits - InCurrent);
										_It.It32->_Last = Seg->Str.s32 + Seg->StrUnits - 1;

									} else {
										// No more segments.
										//
										_It.It32->_Ptr = _It.It32->_Last;

										// Nothing else to do, end loop.
										//
										continue;
									}

								} else {
									// It was all in this segment, move forward.
									//
									_It.It32->_Ptr += InCurrent;
								}
							}

							break;

						case IsWBit_t:

							OneCharUnits = strwidth(_It.ItW->_Ptr, 1);

							// Two possibilities here (1) this segment contain the entire character,
							// (2) the single character is split across segments.
							//
							// (2) can happen with somone appends by character units,
							// and not characters. Hopefully the rest is not an
							// invalid character or missing.
							//
							if (_It.ItW->_Ptr + OneCharUnits < _It.ItW->_Last ) {
								// Fits.
								// Advanced 1 character that is OneCharUnits wide.
								//
								_It.ItW->_Ptr += OneCharUnits;
								ToGo--;
								// Done
								//
								continue;

							} else if (_It.ItW->_Ptr + OneCharUnits == _It.ItW->_Last ) {
								ToGo--;

								if ((_SegmentsOffset + 1) < _Segments->size()) {
									_SegmentsOffset++;
									// Done
									//
									Seg = _Segments->at(_SegmentsOffset);
									_It.ItW->_First = Seg->Str.sW;
									_It.ItW->_Ptr = Seg->Str.sW;
									_It.ItW->_Last = Seg->Str.sW + Seg->StrUnits - 1;

								} else {
									_It.ItW->_Ptr = _It.ItW->_Last;
								}

								continue;

							} else {
								// Does not fit in this segment. Some of it
								// is in the next segment.
								//
								InCurrent = (_It.ItW->_Last - _It.ItW->_Ptr);

								if (OneCharUnits > InCurrent) {

									// Go to the next segment, if exists.
									//
									if ((_SegmentsOffset + 1) < _Segments->size()) {
										_SegmentsOffset++;
										Seg = _Segments->at(_SegmentsOffset);

										// Skip them
										//
										_It.ItW->_First = Seg->Str.sW;
										_It.ItW->_Ptr = Seg->Str.sW + (OneCharUnits - InCurrent);
										_It.ItW->_Last = Seg->Str.sW + Seg->StrUnits - 1;

									} else {
										// No more segments.
										//
										_It.ItW->_Ptr = _It.ItW->_Last;

										// Nothing else to do, end loop.
										//
										continue;
									}

								} else {
									// It was all in this segment, move forward.
									//
									_It.ItW->_Ptr += InCurrent;
								}
							}

							break;
					}
				} while (_SegmentsOffset < (_Segments->size() - 1));

				return;
			}

			void
			String::IteratorBase::_Dec(int64_t CharCount)
			{
				// Back up CharCount characters.
				// When backing up, with any charset, means that we can not backup
				// one character unit width, as charsets exists where it is not
				// always possible to determine just by looking at the previsous
				// character unit, the width of the previous character.
				//
				StringSeg	*	Seg = _Segments->at(_SegmentsOffset);

				// Can't back up before the first segment.
				//
				if (_SegmentsOffset == 0) {

					// Can't back up before the first character in first segment.
					//
					if (_It.It8->_Ptr > _It.It8->_First) {

					}

				} else {
					// Go from the start of the string, and find the start of the
					// previous character.
					//

				}

				return;
			}

			String::iterator::self_type
			String::iterator::operator++()
			{
				if (_Direction == ItForward_t) {
					_Inc(1);

				} else if (_Direction == ItReverse_t) {
					_Dec(1);
				}

				return (*this);
			}

			String::iterator::self_type
			String::iterator::operator++(int /*NOTUSED*/)
			{
				self_type	Results = *this;

				if (_Direction == ItForward_t) {
					_Inc(1);

				} else if (_Direction == ItReverse_t) {
					_Dec(1);
				}

				return (Results);
			}

			String::iterator::self_type
			String::iterator::operator--()
			{
				size_t		Units = 0;

				if (_Direction == ItForward_t) {
					// We have to backup to point to the start of the
					// previous character - of unknown character unit width.
					// So remember current position,
					// Go to _First and count forward, until start of last.
					//

					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								const char	*	StartedAt = _It.It8->_Ptr;
								const char	*	Last = _It.It8->_First;
								const char	*	Ptr = Last;

								while (Ptr != StartedAt) {
									Units = CharacterUnits(Ptr);
									Last = Ptr;
									Ptr += Units;
								}

								// Set to the last character start, before StartedAt.
								//
								_It.It8->_Ptr = Last;
							}
							break;

						case Is16Bit_t: {
								const char16_t	*	StartedAt = _It.It16->_Ptr;
								const char16_t	*	Last = _It.It16->_First;
								const char16_t	*	Ptr = Last;

								while (Ptr != StartedAt) {
									Units = CharacterUnits(Ptr);
									Last = Ptr;
									Ptr += Units;
								}

								// Set to the last character start, before StartedAt.
								//
								_It.It16->_Ptr = Last;
							}
							break;

						case Is32Bit_t: {
								const char32_t	*	StartedAt = _It.It32->_Ptr;
								const char32_t	*	Last = _It.It32->_First;
								const char32_t	*	Ptr = Last;

								while (Ptr != StartedAt) {
									Units = CharacterUnits(Ptr);
									Last = Ptr;
									Ptr += Units;
								}

								// Set to the last character start, before StartedAt.
								//
								_It.It32->_Ptr = Last;
							}
							break;

						case IsWBit_t: {
								const wchar_t	*	StartedAt = _It.ItW->_Ptr;
								const wchar_t	*	Last = _It.ItW->_First;
								const wchar_t	*	Ptr = Last;

								while (Ptr != StartedAt) {
									Units = CharacterUnits(Ptr);
									Last = Ptr;
									Ptr += Units;
								}

								// Set to the last character start, before StartedAt.
								//
								_It.ItW->_Ptr = Last;
							}
							break;
					}

				} else {
					_Inc(1);
				}

				return (*this);
			}

			String::iterator::self_type
			String::iterator::operator--(int /*NotUsed*/)
			{
				self_type	Results(*this);

				if (_Direction == ItForward_t) {
					this->_Dec(1);

				} else if (_Direction == ItReverse_t) {
					this->_Inc(1);
				}

				return (Results);
			}

			String::iterator
			String::iterator::operator+(int64_t Add) const
			{
				iterator		Results(*this);

				if (_Direction == ItForward_t) {
					if (Add > 0) {
						Results._Inc(Add);

					} else {
						Results._Dec(-Add);
					}

				} else if (_Direction == ItReverse_t) {
					if (Add > 0) {
						Results._Dec(Add);

					} else {
						Results._Inc(-Add);
					}
				}

				return (Results);
			}

			String::iterator	&
			String::iterator::operator+=(int64_t Add)
			{
				*this = (*this + Add);

				return (*this);
			}

			String::iterator
			String::iterator::operator-(int64_t Sub) const
			{
				iterator	Results(*this);

				if (_Direction == ItForward_t) {
					if (Sub > 0) {
						Results._Dec(Sub);

					} else {
						Results._Inc(-Sub);
					}

				} else if (_Direction == ItReverse_t) {
					if (Sub > 0) {
						Results._Inc(Sub);

					} else {
						Results._Dec(-Sub);
					}
				}

				return (Results);
			}

			String::iterator	&
			String::iterator::operator-=(int64_t Sub)
			{
				*this = (*this - Sub);

				return (*this);
			}

			int64_t
			String::iterator::operator-(self_type Other)
			{
				int64_t		Results = 0;

				/* NOTE: This is a distance operator (R or F not relevant) */
				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = _It.It8->str() - Other._It.It8->str();
						break;

					case Is16Bit_t:
						Results = _It.It16->str() - Other._It.It16->str();
						break;

					case Is32Bit_t:
						Results = _It.It32->str() - Other._It.It32->str();
						break;

					case IsWBit_t:
						Results = _It.ItW->str() - Other._It.ItW->str();
						break;
				}

				return (Results);
			}

			bool
			String::iterator::operator<(const self_type & Rhs)
			{
				bool		Results = false;

				if (_Direction == ItForward_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 < *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 < *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 < *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW < *Rhs._It.ItW;
							break;
					}

				} else if (_Direction == ItReverse_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 > *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 > *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 > *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW > *Rhs._It.ItW;
							break;
					}
				}

				return (Results);
			}

			bool
			String::iterator::operator<=(const self_type & Rhs)
			{
				bool		Results = false;

				if (_Direction == ItForward_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 <= *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 <= *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 <= *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW <= *Rhs._It.ItW;
							break;
					}

				} else if (_Direction == ItReverse_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 >= *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 >= *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 >= *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW >= *Rhs._It.ItW;
							break;
					}
				}

				return (Results);
			}

			bool
			String::iterator::operator>(const self_type & Rhs)
			{
				bool		Results = false;

				if (_Direction == ItForward_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 > *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 > *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 > *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW > *Rhs._It.ItW;
							break;
					}

				} else if (_Direction == ItReverse_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 < *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 < *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 < *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW < *Rhs._It.ItW;
							break;
					}
				}

				return (Results);
			}

			bool
			String::iterator::operator>=(const self_type & Rhs)
			{
				bool		Results = false;

				if (_Direction == ItForward_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 >= *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 >= *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 >= *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW >= *Rhs._It.ItW;
							break;
					}

				} else if (_Direction == ItReverse_t) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = *_It.It8 <= *Rhs._It.It8;
							break;

						case Is16Bit_t:
							Results = *_It.It16 <= *Rhs._It.It16;
							break;

						case Is32Bit_t:
							Results = *_It.It32 <= *Rhs._It.It32;
							break;

						case IsWBit_t:
							Results = *_It.ItW <= *Rhs._It.ItW;
							break;
					}
				}

				return (Results);
			}

			String::iterator::reference
			String::iterator::operator*() const
			{
				static char32_t	Foo = 0;
				reference	Results = Foo;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = **_It.It8;
						break;

					case Is16Bit_t:
						Results = **_It.It16;
						break;

					case Is32Bit_t:
						Results = **_It.It32;
						break;

					case IsWBit_t:
						Results = **_It.ItW;
						break;
				}

				return (Results);
			}

			String::iterator::pointer
			String::iterator::operator->() const
			{
				pointer		Results = nullptr;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = _It.It8->str();
						break;

					case Is16Bit_t:
						Results = _It.It16->str();
						break;

					case Is32Bit_t:
						Results = _It.It32->str();
						break;

					case IsWBit_t:
						Results = _It.ItW->str();
						break;
				}

				return (Results);
			}

			const char	*
			String::iterator::str8() const
			{
				const char	*	Results = nullptr;

				if (_Width == Is8Bit_t) {
					Results = _It.It8->str();
				}

				return (Results);
			}

			const char16_t	*
			String::iterator::str16() const
			{
				const char16_t	*	Results = nullptr;

				if (_Width == Is16Bit_t) {
					Results = _It.It16->str();
				}

				return (Results);
			}

			const char32_t	*
			String::iterator::str32() const
			{
				const char32_t	*	Results = nullptr;

				if (_Width == Is32Bit_t) {
					Results = _It.It32->str();
				}

				return (Results);
			}

			const wchar_t	*
			String::iterator::strW() const
			{
				const wchar_t	*	Results = nullptr;

				if (_Width == IsWBit_t) {
					Results = _It.ItW->str();
				}

				return (Results);
			}

			bool
			String::iterator::operator==(const self_type & Rhs) const
			{
				bool		Results = false;

				if (_Width == Rhs._Width && _Direction == Rhs._Direction) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = _It.It8->str() == Rhs._It.It8->str();
							break;

						case Is16Bit_t:
							Results = _It.It16->str() == Rhs._It.It16->str();
							break;

						case Is32Bit_t:
							Results = _It.It32->str() == Rhs._It.It32->str();
							break;

						case IsWBit_t:
							Results = _It.ItW->str() == Rhs._It.ItW->str();
							break;
					}
				}

				return (Results);
			}

			bool
			String::iterator::operator!=(const self_type & Rhs) const
			{
				return (!(*this == Rhs));
			}

			String::iterator
			String::iterator::operator[](size_t Offset) const
			{
				self_type		Results;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results._Width = Is8Bit_t;
						delete Results._It.It8;
						Results._It.It8 = new iteratorType<char>(_It.It8[Offset]);
						break;

					case Is16Bit_t:
						Results._Width = Is16Bit_t;
						delete Results._It.It16;
						Results._It.It16 = new iteratorType<char16_t>
						(_It.It16[Offset]);
						break;

					case Is32Bit_t:
						Results._Width = Is32Bit_t;
						delete Results._It.It32;
						Results._It.It32 = new iteratorType<char32_t>
						(_It.It32[Offset]);
						break;

					case IsWBit_t:
						Results._Width = IsWBit_t;
						delete Results._It.ItW;
						Results._It.ItW = new iteratorType<wchar_t>
						(_It.ItW[Offset]);
						break;
				}

				return (Results);
			}

			String::iterator	&
			String::begin()
			{
				iterator	*	Results = nullptr;

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO8, Length(), Is8Bit_t);

						} else {
							Results = new iterator(Get8(), Length(), Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO16, Length(), Is16Bit_t);

						} else {
							Results = new iterator(Get16(), Length(), Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO32, Length(), Is32Bit_t);

						} else {
							Results = new iterator(Get32(), Length(), Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.ROW, Length(), IsWBit_t);

						} else {
							Results = new iterator(GetW(), Length(), IsWBit_t);
						}

						break;

				}

				if (Results != nullptr) {
					Results->_Direction = ItForward_t;
				}

				return (*Results);
			}

			String::iterator	&
			String::rbegin()
			{
				iterator	*	Results = nullptr;

				size_t			Len = Length();

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO8,
							                       _RO->Str.RO8 + Length() - 1,
							                       Length(),
							                       Is8Bit_t);

						} else {
							Results = new iterator(Get8(),
							                       Get8() + Length() - 1,
							                       Length(),
							                       Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO16,
							                       _RO->Str.RO16 + Length() - 1,
							                       Length(),
							                       Is16Bit_t);

						} else {
							Results = new iterator(Get16(),
							                       Get16() + Length() - 1,
							                       Length(),
							                       Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO32,
							                       _RO->Str.RO32 + Length() - 1,
							                       Length(),
							                       Is32Bit_t);

						} else {
							Results = new iterator(Get32(),
							                       Get32() + Length() - 1,
							                       Length(),
							                       Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.ROW,
							                       _RO->Str.ROW + Length() - 1,
							                       Length(),
							                       IsWBit_t);

						} else {
							Results = new iterator(GetW(),
							                       GetW() + Length() - 1,
							                       Length(),
							                       IsWBit_t);
						}

						break;
				}

				if (Results != nullptr) {
					Results->_Direction = ItReverse_t;
				}

				return (*Results);
			}

			String::iterator	&
			String::end()
			{
				iterator	*	Results = nullptr;

				size_t			Len = Length();

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO8,
							                       _RO->Str.RO8 + Len - 1, Len,
							                       Is8Bit_t);

						} else {
							Results = new iterator(Get8(), Get8() + Len - 1, Len,
							                       Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO16,
							                       _RO->Str.RO16 + Len - 1, Len,
							                       Is16Bit_t);

						} else {
							Results = new iterator(Get16(), Get16() + Len - 1, Len,
							                       Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO32,
							                       _RO->Str.RO32 + Len - 1, Len,
							                       Is32Bit_t);

						} else {
							Results = new iterator(Get32(), Get32() + Len - 1, Len,
							                       Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.ROW,
							                       _RO->Str.ROW + Len - 1, Len,
							                       IsWBit_t);

						} else {
							Results = new iterator(GetW(), GetW() + Len - 1, Len,
							                       IsWBit_t);
						}

						break;

				}

				if (Results != nullptr) {
					Results->_Direction = ItForward_t;
				}

				return (*Results);
			}

			String::iterator	&
			String::rend()
			{
				iterator	*	Results = nullptr;

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO8, Length(), Is8Bit_t);

						} else {
							Results = new iterator(Get8(), Length(), Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO16, Length(), Is16Bit_t);

						} else {
							Results = new iterator(Get16(), Length(), Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.RO32, Length(), Is32Bit_t);

						} else {
							Results = new iterator(Get32(), Length(), Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new iterator(_RO->Str.ROW, Length(), IsWBit_t);

						} else {
							Results = new iterator(GetW(), Length(), IsWBit_t);
						}

						break;

				}

				if (Results != nullptr) {
					Results->_Direction = ItReverse_t;
				}

				return (*Results);
			}

			/*
			 * ------------ String::const_iterator
			 */

			String::const_iterator::const_iterator()
			{
				_Width = Is8Bit_t;
				_Direction = ItForward_t;
				memset(&_It, 0, sizeof(_It));


				return;
			}

			String::const_iterator::const_iterator(const const_iterator
			                                       & From)
			{
				_Width = From._Width;
				_Direction = From._Direction;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						_It.It8 = new iteratorType<char>();
						*_It.It8 = *From._It.It8;
						break;

					case Is16Bit_t:
						_It.It16 = new iteratorType<char16_t>();
						*_It.It16 = *From._It.It16;
						break;

					case Is32Bit_t:
						_It.It32 = new iteratorType<char32_t>();
						*_It.It32 = *From._It.It32;
						break;

					case IsWBit_t:
						_It.ItW = new iteratorType<wchar_t>();
						*_It.ItW = *From._It.ItW;
						break;
				}

				return;
			}

			String::const_iterator::const_iterator(const iterator
			                                       & From)
			{
				_Width = From._Width;
				_Direction = From._Direction;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						_It.It8 = new iteratorType<char>();
						*_It.It8 = *From._It.It8;
						break;

					case Is16Bit_t:
						_It.It16 = new iteratorType<char16_t>();
						*_It.It16 = *From._It.It16;
						break;

					case Is32Bit_t:
						_It.It32 = new iteratorType<char32_t>();
						*_It.It32 = *From._It.It32;
						break;

					case IsWBit_t:
						_It.ItW = new iteratorType<wchar_t>();
						*_It.ItW = *From._It.ItW;
						break;
				}

				return;
			}

			String::const_iterator::const_iterator(const char * Ptr,
			                                       size_t Len)
			{
				_Width = Is8Bit_t;
				_Direction = ItForward_t;
				_It.It8 = new iteratorType<char>((const char *)Ptr, Len);

				return;
			}

			String::const_iterator::const_iterator(const char16_t * Ptr,
			                                       size_t Len)
			{
				_Width = Is16Bit_t;
				_Direction = ItForward_t;
				_It.It16 = new iteratorType<char16_t>((const char16_t *)Ptr,
				                                      Len);

				return;
			}

			String::const_iterator::const_iterator(const char32_t * Ptr,
			                                       size_t Len)
			{
				_Width = Is32Bit_t;
				_Direction = ItForward_t;
				_It.It32 = new iteratorType<char32_t>((const char32_t *)Ptr,
				                                      Len);

				return;
			}

			String::const_iterator::const_iterator(const wchar_t * Ptr,
			                                       size_t Len)
			{
				_Width = IsWBit_t;
				_Direction = ItForward_t;
				_It.ItW = new iteratorType<wchar_t>((const wchar_t *)Ptr,
				                                    Len);

				return;
			}

			String::const_iterator::const_iterator(
			    String::const_iterator::pointer Ptr,
			    size_t Len,
			    CharacterUnitWidth_e cWidth)
			{
				_Width = cWidth;
				_Direction = ItForward_t;

				switch (_Width) {

					case IsUnknownBit_t:
						memset(&_It, 0, sizeof(_It));
						break;

					case Is8Bit_t:
						_It.It8 = new iteratorType<char>((const char *)Ptr, Len);
						break;

					case Is16Bit_t:
						_It.It16 = new iteratorType<char16_t>((char16_t *)Ptr, Len);
						break;

					case Is32Bit_t:
						_It.It32 = new iteratorType<char32_t>((char32_t *)Ptr, Len);
						break;

					case IsWBit_t:
						_It.ItW = new iteratorType<wchar_t>((wchar_t *)Ptr, Len);
						break;
				}

				return;
			}

			String::const_iterator::const_iterator(pointer Start,
			                                       pointer Ptr,
			                                       size_t Len,
			                                       CharacterUnitWidth_e cWidth)
			{
				_Width = cWidth;
				_Direction = ItForward_t;

				if (Ptr < Start) {
					Ptr = Start;
				}

				switch (_Width) {

					case IsUnknownBit_t:
						memset(&_It, 0, sizeof(_It));
						break;

					case Is8Bit_t:
						if ((char *)Ptr > ((char *)Start + Len)) {
							Ptr = (char *)Start + Len;
						}

						_It.It8 = new iteratorType<char>((char *)Start,
						                                 (char *)Ptr,
						                                 Len);
						break;

					case Is16Bit_t:
						if ((char16_t *)Ptr > ((char16_t *)Start + Len)) {
							Ptr = (char16_t *)Start + Len;
						}

						_It.It16 = new iteratorType<char16_t>((char16_t *)Start,
						                                      (char16_t *)Ptr,
						                                      Len);
						break;

					case Is32Bit_t:
						if ((char32_t *)Ptr > ((char32_t *)Start + Len)) {
							Ptr = (char32_t *)Start + Len;
						}

						_It.It32 = new iteratorType<char32_t>((char32_t *)Start,
						                                      (char32_t *)Ptr,
						                                      Len);
						break;

					case IsWBit_t:
						if ((wchar_t *)Ptr > ((wchar_t *)Start + Len)) {
							Ptr = (wchar_t *)Start + Len;
						}

						_It.ItW = new iteratorType<wchar_t>((wchar_t *)Start,
						                                    (wchar_t *)Ptr,
						                                    Len);
						break;
				}

				return;
			}

			String::const_iterator::const_iterator(const char * Start,
			                                       const char * Ptr,
			                                       size_t Len)
			{
				_Width = Is8Bit_t;
				_Direction = ItForward_t;
				_It.It8 = new iteratorType<char>((char *)Start,
				                                 (char *)Ptr,
				                                 Len);
				return;
			}

			String::const_iterator::const_iterator(const char16_t *
			                                       Start,
			                                       const char16_t * Ptr,
			                                       size_t Len)
			{
				_Width = Is16Bit_t;
				_Direction = ItForward_t;
				_It.It16 = new iteratorType<char16_t>((char16_t *)Start,
				                                      (char16_t *)Ptr,
				                                      Len);
				return;
			}

			String::const_iterator::const_iterator(const char32_t *
			                                       Start,
			                                       const char32_t * Ptr,
			                                       size_t Len)
			{
				_Width = Is32Bit_t;
				_Direction = ItForward_t;
				_It.It32 = new iteratorType<char32_t>((char32_t *)Start,
				                                      (char32_t *)Ptr,
				                                      Len);
				return;
			}

			String::const_iterator::const_iterator(const wchar_t *
			                                       Start,
			                                       const wchar_t * Ptr,
			                                       size_t Len)
			{
				_Width = IsWBit_t;
				_Direction = ItForward_t;
				_It.ItW = new iteratorType<wchar_t>((wchar_t *)Start,
				                                    (wchar_t *)Ptr,
				                                    Len);
				return;
			}

			CharacterUnitWidth_e
			String::const_iterator::Width() const
			{
				return (_Width);
			}

			String::const_iterator::self_type
			String::const_iterator::operator=(const self_type & Other)
			{
				_Width = Other._Width;
				_Direction = Other._Direction;

				switch (_Width) {

					case IsUnknownBit_t:
						memset(&_It, 0, sizeof(_It));
						break;

					case Is8Bit_t:
						_It.It8 = new iteratorType<char>(*Other._It.It8);
						break;

					case Is16Bit_t:
						_It.It16 = new iteratorType<char16_t>(*Other._It.It16);
						break;

					case Is32Bit_t:
						_It.It32 = new iteratorType<char32_t>(*Other._It.It32);
						break;

					case IsWBit_t:
						_It.ItW = new iteratorType<wchar_t>(*Other._It.ItW);
						break;
				}

				return (*this);
			}

			String::const_iterator::self_type
			String::const_iterator::operator++()
			{
				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_Direction == ItForward_t) {
							++(*_It.It8);

						} else {
							--(*_It.It8);
						}

						break;

					case Is16Bit_t:
						if (_Direction == ItForward_t) {
							++(*_It.It16);

						} else {
							--(*_It.It16);
						}

						break;

					case Is32Bit_t:
						if (_Direction == ItForward_t) {
							++(*_It.It32);

						} else {
							--(*_It.It32);
						}

						break;

					case IsWBit_t:
						if (_Direction == ItForward_t) {
							++(*_It.ItW);

						} else {
							--(*_It.ItW);
						}

						break;
				}

				return (*this);
			}


			String::const_iterator::self_type
			String::const_iterator::operator++(int /*NOTUSED*/)
			{
				self_type	Results = *this;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_Direction == ItForward_t) {
							(*_It.It8)++;

						} else {
							(*_It.It8)--;
						}

						break;

					case Is16Bit_t:
						if (_Direction == ItForward_t) {
							(*_It.It16)++;

						} else {
							(*_It.It16)--;
						}

						break;

					case Is32Bit_t:
						if (_Direction == ItForward_t) {
							(*_It.It32)++;

						} else {
							(*_It.It32)--;
						}

						break;

					case IsWBit_t:
						if (_Direction == ItForward_t) {
							(*_It.ItW)++;

						} else {
							(*_It.ItW)--;
						}

						break;
				}

				return (Results);
			}

			String::const_iterator::self_type
			String::const_iterator::operator--()
			{
				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_Direction == ItForward_t) {
							--(*_It.It8);

						} else {
							++(*_It.It8);
						}

						break;

					case Is16Bit_t:
						if (_Direction == ItForward_t) {
							--(*_It.It16);

						} else {
							++(*_It.It16);
						}

						break;

					case Is32Bit_t:
						if (_Direction == ItForward_t) {
							--(*_It.It32);

						} else {
							++(*_It.It32);
						}

						break;

					case IsWBit_t:
						if (_Direction == ItForward_t) {
							--(*_It.ItW);

						} else {
							++(*_It.ItW);
						}

						break;
				}

				return (*this);
			}

			String::const_iterator::self_type
			String::const_iterator::operator--(int /*NotUsed*/)
			{
				self_type	Results(*this);

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_Direction == ItForward_t) {
							(*_It.It8)--;

						} else {
							(*_It.It8)++;
						}

						break;

					case Is16Bit_t:
						if (_Direction == ItForward_t) {
							(*_It.It16)--;

						} else {
							(*_It.It16)++;
						}

						break;

					case Is32Bit_t:
						if (_Direction == ItForward_t) {
							(*_It.It32)--;

						} else {
							(*_It.It32)++;
						}

						break;

					case IsWBit_t:
						if (_Direction == ItForward_t) {
							(*_It.ItW)--;

						} else {
							(*_It.ItW)++;
						}

						break;
				}

				return (Results);
			}

			String::const_iterator::self_type
			String::const_iterator::operator+(int64_t Add) const
			{
				const_iterator	*	Results = new const_iterator(*this);

				if (_Direction == ItForward_t) {
					if (Add > 0) {
						Results->_Inc(Add);

					} else if (Add < 0) {
						Results->_Dec(-Add);
					}

				} else if (_Direction == ItReverse_t) {
					if (Add > 0) {
						Results->_Dec(Add);

					} else if (Add < 0) {
						Results->_Inc(-Add);
					}
				}

				return (*Results);
			}

			String::const_iterator::self_type	&
			String::const_iterator::operator+=(int64_t Add)
			{
				*this = (*this + Add);

				return (*this);
			}

			String::const_iterator::self_type
			String::const_iterator::operator-(int64_t Sub) const
			{
				const_iterator		Results(*this);

				if (_Direction == ItForward_t) {
					if (Sub > 0) {
						Results._Dec(Sub);

					} else {
						Results._Inc(-Sub);
					}

				} else if (_Direction == ItReverse_t) {
					if (Sub > 0) {
						Results._Inc(Sub);

					} else {
						Results._Dec(-Sub);
					}
				}

				return (Results);
			}

			String::const_iterator::self_type	&
			String::const_iterator::operator-=(int64_t Sub)
			{
				*this = (*this - Sub);

				return (*this);
			}

			/*
			 * This is a difference operator in iterators, direction
			 * not relavant
			 */
			int64_t
			String::const_iterator::operator-(self_type & Other)
			{
				int64_t		Results = 0;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = _It.It8->str() - Other._It.It8->str();
						break;

					case Is16Bit_t:
						Results = _It.It16->str() - Other._It.It16->str();
						break;

					case Is32Bit_t:
						Results = _It.It32->str() - Other._It.It32->str();
						break;

					case IsWBit_t:
						Results = _It.ItW->str() - Other._It.ItW->str();

						break;
				}

				return (Results);
			}

			bool
			String::const_iterator::operator<(const self_type & Rhs)
			{
				bool		Results = false;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = *_It.It8 < *Rhs._It.It8;
						break;

					case Is16Bit_t:
						Results = *_It.It16 < *Rhs._It.It16;
						break;

					case Is32Bit_t:
						Results = *_It.It32 < *Rhs._It.It32;
						break;

					case IsWBit_t:
						Results = *_It.ItW < *Rhs._It.ItW;
						break;
				}

				return (Results);
			}

			bool
			String::const_iterator::operator<=(const self_type & Rhs)
			{
				bool		Results = false;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = *_It.It8 <= *Rhs._It.It8;
						break;

					case Is16Bit_t:
						Results = *_It.It16 <= *Rhs._It.It16;
						break;

					case Is32Bit_t:
						Results = *_It.It32 <= *Rhs._It.It32;
						break;

					case IsWBit_t:
						Results = *_It.ItW <= *Rhs._It.ItW;
						break;
				}

				return (Results);
			}

			bool
			String::const_iterator::operator>(const self_type & Rhs)
			{
				bool		Results = false;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = *_It.It8 > *Rhs._It.It8;
						break;

					case Is16Bit_t:
						Results = *_It.It16 > *Rhs._It.It16;
						break;

					case Is32Bit_t:
						Results = *_It.It32 > *Rhs._It.It32;
						break;

					case IsWBit_t:
						Results = *_It.ItW > *Rhs._It.ItW;
						break;
				}

				return (Results);
			}

			bool
			String::const_iterator::operator>=(const self_type & Rhs)
			{
				bool		Results = false;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = *_It.It8 >= *Rhs._It.It8;
						break;

					case Is16Bit_t:
						Results = *_It.It16 >= *Rhs._It.It16;
						break;

					case Is32Bit_t:
						Results = *_It.It32 >= *Rhs._It.It32;
						break;

					case IsWBit_t:
						Results = *_It.ItW >= *Rhs._It.ItW;
						break;
				}

				return (Results);
			}

			String::const_iterator::reference
			String::const_iterator::operator*() const
			{
				static char32_t	Foo = 0;
				reference	Results = Foo;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = **_It.It8;
						break;

					case Is16Bit_t:
						Results = **_It.It16;
						break;

					case Is32Bit_t:
						Results = **_It.It32;
						break;

					case IsWBit_t:
						Results = **_It.ItW;
						break;
				}

				return (Results);
			}

			String::const_iterator::pointer
			String::const_iterator::operator->() const
			{
				pointer		Results = nullptr;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = _It.It8->str();
						break;

					case Is16Bit_t:
						Results = _It.It16->str();
						break;

					case Is32Bit_t:
						Results = _It.It32->str();
						break;

					case IsWBit_t:
						Results = _It.ItW->str();
						break;
				}

				return (Results);
			}

			const char	*
			String::const_iterator::str8() const
			{
				const char	*	Results = nullptr;

				if (_Width == Is8Bit_t) {
					Results = _It.It8->str();
				}

				return (Results);
			}

			const char16_t	*
			String::const_iterator::str16() const
			{
				const char16_t	*	Results = nullptr;

				if (_Width == Is16Bit_t) {
					Results = _It.It16->str();
				}

				return (Results);
			}

			const char32_t	*
			String::const_iterator::str32() const
			{
				const char32_t	*	Results = nullptr;

				if (_Width == Is32Bit_t) {
					Results = _It.It32->str();
				}

				return (Results);
			}

			const wchar_t	*
			String::const_iterator::strW() const
			{
				const wchar_t	*	Results = nullptr;

				if (_Width == IsWBit_t) {
					Results = _It.ItW->str();
				}

				return (Results);
			}

			bool
			String::const_iterator::operator==(const self_type & Rhs)
			const
			{
				bool		Results = false;

				if (_Width == Rhs._Width && _Direction == Rhs._Direction) {
					switch (_Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = _It.It8->str() == Rhs._It.It8->str();
							break;

						case Is16Bit_t:
							Results = _It.It16->str() == Rhs._It.It16->str();
							break;

						case Is32Bit_t:
							Results = _It.It32->str() == Rhs._It.It32->str();
							break;

						case IsWBit_t:
							Results = _It.ItW->str() == Rhs._It.ItW->str();
							break;
					}
				}

				return (Results);
			}

			bool
			String::const_iterator::operator!=(const self_type & Rhs)
			const
			{
				return (!(*this == Rhs));
			}

			String::const_iterator::self_type
			String::const_iterator::operator[](size_t Offset) const
			{
				self_type		Results;

				switch (_Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results._Width = Is8Bit_t;
						delete Results._It.It8;
						Results._It.It8 = new iteratorType<char>(_It.It8[Offset]);
						break;

					case Is16Bit_t:
						Results._Width = Is16Bit_t;
						delete Results._It.It16;
						Results._It.It16 = new iteratorType<char16_t>
						(_It.It16[Offset]);
						break;

					case Is32Bit_t:
						Results._Width = Is32Bit_t;
						delete Results._It.It32;
						Results._It.It32 = new iteratorType<char32_t>
						(_It.It32[Offset]);
						break;

					case IsWBit_t:
						Results._Width = IsWBit_t;
						delete Results._It.ItW;
						Results._It.ItW = new iteratorType<wchar_t>
						(_It.ItW[Offset]);
						break;
				}

				return (Results);
			}

			String::const_iterator	&
			String::cbegin() const
			{
				const_iterator	*	Results = nullptr;

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO8, Length(),
							                             Is8Bit_t);

						} else {
							Results = new const_iterator(Get8(), Length(), Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO16, Length(),
							                             Is16Bit_t);

						} else {
							Results = new const_iterator(Get16(), Length(), Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO32, Length(),
							                             Is32Bit_t);

						} else {
							Results = new const_iterator(Get32(), Length(), Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.ROW, Length(),
							                             IsWBit_t);

						} else {
							Results = new const_iterator(GetW(), Length(), IsWBit_t);
						}

						break;
				}

				if (Results != nullptr) {
					Results->_Direction = ItForward_t;
				}

				return (*Results);
			}

			String::const_iterator	&
			String::crbegin() const
			{
				const_iterator	*	Results = nullptr;

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO8,
							                             _RO->Str.RO8 + Length() - 1,
							                             Length(),
							                             Is8Bit_t);

						} else {
							Results = new const_iterator(Get8(),
							                             Get8() + Length() - 1,
							                             Length(),
							                             Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO16,
							                             _RO->Str.RO16 + Length() - 1,
							                             Length(),
							                             Is16Bit_t);

						} else {
							Results = new const_iterator(Get16(),
							                             Get16() + Length() - 1,
							                             Length(),
							                             Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO32,
							                             _RO->Str.RO32 + Length() - 1,
							                             Length(),
							                             Is32Bit_t);

						} else {
							Results = new const_iterator(Get32(),
							                             Get32() + Length() - 1,
							                             Length(),
							                             Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.ROW,
							                             _RO->Str.ROW + Length() - 1,
							                             Length(),
							                             IsWBit_t);

						} else {
							Results = new const_iterator(GetW(),
							                             GetW() + Length() - 1,
							                             Length(),
							                             IsWBit_t);
						}

						break;
				}

				if (Results != nullptr) {
					Results->_Direction = ItReverse_t;
				}

				return (*Results);
			}

			String::const_iterator	&
			String::cend() const
			{
				const_iterator	*	Results = nullptr;

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO8,
							                             _RO->Str.RO8 + Length() - 1,
							                             Length(),
							                             Is8Bit_t);

						} else {
							Results = new const_iterator(Get8(),
							                             Get8() + Length() - 1,
							                             Length(),
							                             Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO16,
							                             _RO->Str.RO16 + Length() - 1,
							                             Length(),
							                             Is16Bit_t);

						} else {
							Results = new const_iterator(Get16(),
							                             Get16() + Length() - 1,
							                             Length(),
							                             Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO32,
							                             _RO->Str.RO32 + Length() - 1,
							                             Length(),
							                             Is32Bit_t);

						} else {
							Results = new const_iterator(Get32(),
							                             Get32() + Length() - 1,
							                             Length(),
							                             Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.ROW,
							                             _RO->Str.ROW + Length() - 1,
							                             Length(),
							                             IsWBit_t);

						} else {
							Results = new const_iterator(GetW(),
							                             GetW() + Length() - 1,
							                             Length(),
							                             IsWBit_t);
						}

						break;

				}

				if (Results != nullptr) {
					Results->_Direction = ItForward_t;
				}

				return (*Results);
			}

			String::const_iterator	&
			String::crend() const
			{
				const_iterator	*	Results = nullptr;

				switch (InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO8,
							                             Length(),
							                             Is8Bit_t);

						} else {
							Results = new const_iterator(Get8(), Length(), Is8Bit_t);
						}

						break;

					case Is16Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO16,
							                             Length(),
							                             Is16Bit_t);

						} else {
							Results = new const_iterator(Get16(), Length(), Is16Bit_t);
						}

						break;

					case Is32Bit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.RO32,
							                             Length(),
							                             Is32Bit_t);

						} else {
							Results = new const_iterator(Get32(), Length(), Is32Bit_t);
						}

						break;

					case IsWBit_t:
						if (_ROString) {
							Results = new const_iterator(_RO->Str.ROW,
							                             Length(),
							                             IsWBit_t);

						} else {
							Results = new const_iterator(GetW(), Length(), IsWBit_t);
						}

						break;
				}

				if (Results != nullptr) {
					Results->_Direction = ItReverse_t;
				}

				return (*Results);
			}

			String::iterator	&
			String::begin(const char * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}
			String::iterator	&
			String::rbegin(const char * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Results->_It.It8->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::iterator		&
			String::begin(const char16_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::iterator::self_type	&
			String::rbegin(const char16_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Results->_It.It16->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::iterator		&
			String::begin(const char32_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::iterator::self_type	&
			String::rbegin(const char32_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Results->_It.It32->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::iterator		&
			String::begin(const wchar_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::iterator::self_type	&
			String::rbegin(const wchar_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Results->_It.ItW->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::iterator		&
			String::end(const char * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Results->_It.It8->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::iterator::self_type	&
			String::rend(const char * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Results->_It.It8->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::iterator		&
			String::end(const char16_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Results->_It.It16->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::iterator::self_type	&
			String::rend(const char16_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Start;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::iterator		&
			String::end(const char32_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Results->_It.It32->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::iterator::self_type	&
			String::rend(const char32_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Start;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::iterator		&
			String::end(const wchar_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Results->_It.ItW->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::iterator::self_type	&
			String::rend(const wchar_t * Start)
			{
				iterator			*		Results = new iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Start;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cbegin(const char * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crbegin(const char * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Results->_It.It8->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cbegin(const char16_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crbegin(const char16_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Results->_It.It16->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cbegin(const char32_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crbegin(const char32_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Results->_It.It32->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cbegin(const wchar_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Start;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crbegin(const wchar_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Results->_It.ItW->_Last;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cend(const char * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Results->_It.It8->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crend(const char * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is8Bit_t;
				Results->_It.It8 = new	String::iteratorType<char>();
				Results->_It.It8->_First = Start;
				Results->_It.It8->_Last = &Start[strlen(Start) - 1];
				Results->_It.It8->_Ptr = Start;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cend(const char16_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Results->_It.It16->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crend(const char16_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is16Bit_t;
				Results->_It.It16 = new	String::iteratorType<char16_t>();
				Results->_It.It16->_First = Start;
				Results->_It.It16->_Last = &Start[strlen(Start) - 1];
				Results->_It.It16->_Ptr = Start;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cend(const char32_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Results->_It.It32->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crend(const char32_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = Is32Bit_t;
				Results->_It.It32 = new	String::iteratorType<char32_t>();
				Results->_It.It32->_First = Start;
				Results->_It.It32->_Last = &Start[strlen(Start) - 1];
				Results->_It.It32->_Ptr = Start;
				Results->_Direction = ItReverse_t;

				return (*Results);
			}

			String::const_iterator		&
			String::cend(const wchar_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Results->_It.ItW->_Last;
				Results->_Direction = ItForward_t;

				return (*Results);
			}

			String::const_iterator	&
			String::crend(const wchar_t * Start)
			{
				const_iterator			*		Results = new const_iterator;

				Results->_Width = IsWBit_t;
				Results->_It.ItW = new	String::iteratorType<wchar_t>();
				Results->_It.ItW->_First = Start;
				Results->_It.ItW->_Last = &Start[strlen(Start) - 1];
				Results->_It.ItW->_Ptr = Start;

				return (*Results);
			}

		}
	}
}
