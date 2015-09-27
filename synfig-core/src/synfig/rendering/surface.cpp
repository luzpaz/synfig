/* === S Y N F I G ========================================================= */
/*!	\file synfig/rendering/surface.cpp
**	\brief Surface
**
**	$Id$
**
**	\legal
**	......... ... 2015 Ivan Mahonin
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#ifndef WIN32
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

#include "surface.h"

#endif

using namespace synfig;
using namespace rendering;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

rendering::Surface::Surface():
	width(0),
	height(0),
	created(false),
	is_temporary(false),
	used_rect(0, 0, 0, 0)
{ }

rendering::Surface::~Surface() { destroy(); }

void
rendering::Surface::set_size(int width, int height)
{
	assert(!is_created());
	this->width = width > 0 ? width : 0;
	this->height = height > 0 ? height : 0;
}

bool
rendering::Surface::create()
{
	if (!is_created() && !empty())
		created = create_vfunc();
	return is_created();
}


bool
rendering::Surface::assign(const Handle &surface)
{
	destroy();
	if (surface) {
		set_size(surface->get_width(), surface->get_height());
		created = assign_vfunc(*surface);
	} else {
		set_size(0, 0);
	}
	return is_created();
}

void
rendering::Surface::destroy()
{
	if (is_created())
	{
		destroy_vfunc();
		created = false;
	}
}

bool
rendering::Surface::empty() const
{
	return width <= 0 || height <= 0;
}

size_t
rendering::Surface::get_buffer_size() const
{
	// TODO: check limits
	return empty() ? 0 : get_pixels_count() * sizeof(Color);
}

bool
rendering::Surface::get_pixels(Color *buffer) const
{
	return is_created() && get_pixels_vfunc(buffer);
}

/* === E N T R Y P O I N T ================================================= */