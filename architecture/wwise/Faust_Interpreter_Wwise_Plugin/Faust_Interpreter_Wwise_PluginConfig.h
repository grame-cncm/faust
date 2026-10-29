/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2025 Audiokinetic Inc.
*******************************************************************************/

#ifndef Faust_Interpreter_Wwise_PluginConfig_H
#define Faust_Interpreter_Wwise_PluginConfig_H

// NB: In order to properly change the CompanyID / PluginID, you must change them:
// - In this file;
// - In the xml file located in the WwisePlugin directory;
// - In the xml file located in the FactoryAssets directory.
namespace Faust_Interpreter_Wwise_PluginConfig
{
    static const unsigned short CompanyID = 64;
    static const unsigned short PluginID = 16291;
}

#endif // Faust_Interpreter_Wwise_PluginConfig_H
