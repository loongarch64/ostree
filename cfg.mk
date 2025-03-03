export VC_LIST_EXCEPT_DEFAULT=^(rust-bindings/.*|docs/.*|git.mk|lib/.*|m4/.*|md5/.*|build-aux/.*|src/gettext\.h|.*ChangeLog|buildutil/.*)$$

local-checks-to-skip = \
    sc_const_long_option \
    sc_error_message_uppercase \
    sc_file_system \
    sc_immutable_NEWS \
    sc_copyright_check \
    sc_makefile_path_separator_check \
    sc_require_config_h \
    sc_require_config_h_first \
    sc_two_space_separator_in_usage \
    sc_useless_cpp_parens \
    \
    sc_prohibit_atoi_atof \
    sc_prohibit_strcmp \
    sc_cast_of_alloca_return_value \
    sc_cast_of_x_alloc_return_value \
    sc_prohibit_S_IS_definition \
    \
    sc_program_name \
    sc_bindtextdomain	 \
    sc_prohibit_path_max_allocation \
    sc_trailing_blank \

sc_glnx_prefix_error_colon:
	@prohibit='\<glnx_prefix_error *\(.*: ",' halt="don't add trailing : for glnx_prefix_error"	\
	  $(_sc_search_regexp)

sc_glnx_errno_prefix_colon:
	@prohibit='\<glnx_throw_errno_prefix *\(.*: ",' halt="don't add trailing : for glnx_throw_errno_prefix"	\
	  $(_sc_search_regexp)

sc_glnx_no_fd_close:
	@prohibit='\<glnx_fd_close int' halt="Use glnx_autofd, not glnx_fd_close"	\
	  $(_sc_search_regexp)

#SHELL=bash -x
show-vc-list-except:
	@$(VC_LIST_EXCEPT)

VC_LIST_ALWAYS_EXCLUDE_REGEX = ^ABOUT-NLS|cfg.mk|maint.mk|*.md|*.gpg|*.sig|.xz|.gz$$
