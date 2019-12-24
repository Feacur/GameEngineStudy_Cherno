-- https://github.com/premake/premake-core/wiki/Overrides-and-Call-Arrays
require('vstudio')

premake.override(premake.vstudio.vc2010, "project", function(base, prj)
	base(prj)
	premake.w('<!-- Generated by Premake ' .. _PREMAKE_VERSION .. ' -->')
end)

premake.override(premake.vstudio.vc2010.elements, "clCompile", function(base, prj)
	local function setUseFullPathsFalse(prj)
		premake.w('<UseFullPaths>false</UseFullPaths>')
	end
	
	local calls = base(prj)
	table.insert(calls, setUseFullPathsFalse)
	return calls
end)