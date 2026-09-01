/*
 * Copyright (C) 2023-24 Paranoid Android
 *
 * SPDX-License-Identifier: Apache-2.0
 */

package co.aospa.dolby

import android.os.Bundle
import co.aospa.dolby.preference.DolbySettingsFragment
import com.android.settingslib.collapsingtoolbar.FragmentActivity

private const val TAG = "DolbyActivity"

class DolbyActivity : FragmentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        supportFragmentManager.beginTransaction()
            .replace(android.R.id.content, DolbySettingsFragment(), TAG)
            .commit()
    }
}
