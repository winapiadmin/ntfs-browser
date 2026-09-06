#pragma once

#include "attr-resident.h"
#include "attr/volume-information.h"

#include <ntfs-browser/strategy.h>

#include <ntfs-browser/data/attr-header-common.h>
#include <ntfs-browser/file-record.h>

namespace NtfsBrowser
{

template <typename RESIDENT, Strategy S>
class AttrVolInfo : public RESIDENT
{
 public:
  AttrVolInfo(const AttrHeaderCommon& ahc, const FileRecord<S>& fr);
  AttrVolInfo(AttrVolInfo&& other) noexcept = delete;
  AttrVolInfo(AttrVolInfo const& other) = delete;
  AttrVolInfo& operator=(AttrVolInfo&& other) noexcept = delete;
  AttrVolInfo& operator=(AttrVolInfo const& other) = delete;

  ~AttrVolInfo() override;

 private:
  Attr::VolumeInformation vol_info_;

 public:
  // Get NTFS Volume Version
  [[nodiscard]] std::pair<BYTE, BYTE> GetVersion() const noexcept;
};  // AttrVolInfo

}  // namespace NtfsBrowser