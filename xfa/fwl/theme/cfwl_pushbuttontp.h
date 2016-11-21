// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_FWL_THEME_CFWL_PUSHBUTTONTP_H_
#define XFA_FWL_THEME_CFWL_PUSHBUTTONTP_H_

#include <memory>

#include "xfa/fwl/theme/cfwl_widgettp.h"

class CFWL_PushButtonTP : public CFWL_WidgetTP {
 public:
  CFWL_PushButtonTP();
  ~CFWL_PushButtonTP() override;

  // CFWL_WidgetTP
  void Initialize() override;
  void Finalize() override;
  bool IsValidWidget(IFWL_Widget* pWidget) override;
  void DrawBackground(CFWL_ThemeBackground* pParams) override;
  void* GetCapacity(CFWL_ThemePart* pThemePart,
                    CFWL_WidgetCapacity dwCapacity) override;

 protected:
  struct PBThemeData {
    FX_ARGB clrBorder[5];
    FX_ARGB clrStart[5];
    FX_ARGB clrEnd[5];
    FX_ARGB clrFill[5];
  };

  void SetTopLineColor(uint32_t* pData);
  void SetLeftLineColor(uint32_t* pData);
  void SetRightLineColor(uint32_t* pData);
  void SetBottomLineColor(uint32_t* pData);
  void SetBackgroudColor(uint32_t* pData);
  void SetCaptionColor(uint32_t* pData);
  void SetCornerColor(uint32_t* pData);

  int32_t GetColorID(uint32_t dwStates) const;

  std::unique_ptr<PBThemeData> m_pThemeData;

 private:
  void SetThemeData();
};

#endif  // XFA_FWL_THEME_CFWL_PUSHBUTTONTP_H_
