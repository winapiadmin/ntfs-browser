#include <cstring>
#include <stdexcept>

#include "attr-vol-info.h"
#include "ntfs-common.h"

namespace NtfsBrowser
{

template <typename RESIDENT, Strategy S>
AttrVolInfo<RESIDENT, S>::AttrVolInfo(const AttrHeaderCommon& ahc,
                                      const FileRecord<S>& fr)
    : RESIDENT(ahc, fr),
      vol_info_()
{
  const BYTE* data = this->GetData();
  ULONGLONG dataSize = this->GetDataSize();

  if (dataSize < sizeof(Attr::VolumeInformation))
  {
    // Handle case where on-disk data is smaller than expected struct
    // (e.g., missing reserved2 field). Zero-initialize and copy what we have.
    memset(&vol_info_, 0, sizeof(vol_info_));
    if (dataSize > 0)
    {
      memcpy(&vol_info_, data, static_cast<size_t>(dataSize));
    }
  }
  else
  {
    vol_info_ = *reinterpret_cast<const Attr::VolumeInformation*>(data);
  }

  NTFS_TRACE("Attribute: Volume Information\n");
}

template <typename RESIDENT, Strategy S>
AttrVolInfo<RESIDENT, S>::~AttrVolInfo()
{
  NTFS_TRACE("AttrVolInfo deleted\n");
}

template <typename RESIDENT, Strategy S>
std::pair<BYTE, BYTE> AttrVolInfo<RESIDENT, S>::GetVersion() const noexcept
{
  return {vol_info_.major_version, vol_info_.minor_version};
}

template class AttrVolInfo<AttrResidentFullCache, Strategy::FULL_CACHE>;
template class AttrVolInfo<AttrResidentNoCache, Strategy::NO_CACHE>;

}  // namespace NtfsBrowser
