file(REMOVE_RECURSE
  "libpipeline.a"
  "libpipeline.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/pipeline.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
