/*
* Copyright 2018 NXP.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of the NXP Semiconductor nor the names of its
* contributors may be used to endorse or promote products derived from this
* software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

#include <string>
#include <vector>

using namespace std;

#include "libuuu.h"
#include "liberror.h"

struct  notify_map
{
	notify_fun f;
	void *data;
};

static vector<struct notify_map> g_notify_callback_list;

int register_notify_callback(notify_fun f, void *data)
{
	notify_map a;
	a.f = f;
	a.data = data;

	for (size_t i = 0; i < g_notify_callback_list.size(); i++)
	{
		if (g_notify_callback_list[i].f == f)
			return 0;
	}

	g_notify_callback_list.push_back(a);
	return 0;
}

int unregister_notify_callback(notify_fun f)
{
	vector<struct notify_map>::iterator it=g_notify_callback_list.begin();

	for (it;it!=g_notify_callback_list.end();it++)
	{
		if (it->f == f)
		{
			g_notify_callback_list.erase(it);
			return 0;
		}
	}
	return 0;
}

void call_notify(struct notify nf)
{
	vector<struct notify_map>::iterator it = g_notify_callback_list.begin();

	for (it; it != g_notify_callback_list.end(); it++)
	{
		it->f(nf, it->data);
	}
}