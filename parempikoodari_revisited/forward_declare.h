#pragma once

#define CRM_FORWARD_DECLARE_0(c) class c
#define CRM_FORWARD_DECLARE_1(n1, c) namespace n1 { class c; }
#define CRM_FORWARD_DECLARE_2(n1, n2, c) namespace n1 { namespace n2 { class c; } }
